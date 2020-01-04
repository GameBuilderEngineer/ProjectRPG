//===================================================================================================================================
//�yInput.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/19
// [�X�V��]2019/09/19
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Input.h"

//===================================================================================================================================
//�yusing namespace�z
//===================================================================================================================================
using namespace inputNS;

//===================================================================================================================================
//�y�O���[�o���ϐ��z
//===================================================================================================================================
static Input* pointerInput = NULL;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
Input::Input()
{
	//�O���[�o���ϐ��փ|�C���^��ݒ�
	pointerInput = this;

	// �L�[��������Ă����Ԃ������z����N���A
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		keysDown[i] = false;
	}
	// �L�[�������ꂽ���Ƃ������z����N���A
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		keysPressed[i] = false;
	}
	newLine = true;			// �V�����s���J�n
	textIn = "";			// textIn���N���A
	charIn = 0;				// charIn���N���A

	// �}�E�X�f�[�^
	mouseX = 0;				// ���X
	mouseY = 0;				// ���Y
	mouseRawX = 0;			// ������X
	mouseRawY = 0;			// ������Y
	mouseLButton = false;	// ���}�E�X�{�^����������Ă���ꍇ��true
	mouseMButton = false;	// �����}�E�X�{�^����������Ă���ꍇ��true
	mouseRButton = false;	// �E�}�E�X�{�^����������Ă���ꍇ��true
	mouseX1Button = false;	// X1�}�E�X�{�^����������Ă���ꍇ��true
	mouseX2Button = false;	// X2�}�E�X�{�^����������Ă���ꍇ��true
	wheelFraction = 0;		//��]�ʂ̒[��
	zDelta = 0;
	mouseWheelState = MOUSE_WHEEL_STATE::NONE;
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
Input::~Input()
{
	pointerInput = NULL;
	if (mouseCaptured)
	{
		ReleaseCapture(); // �}�E�X�����
	}
}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
HRESULT Input::initialize(HINSTANCE instance,HWND _wnd,bool capture)
{
	wnd = _wnd;
	//------------------------------------------------
	// �����׃}�E�X��o�^
	mouseCaptured = capture;
	if (mouseCaptured)
	{
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = wnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
	}
	//------------------------------------------------

	//------------------------------------------------
	// �uDirectInput�v�I�u�W�F�N�g�̍쐬
	MFAIL(DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dinput, NULL),
		"DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B");

	enumDInputNum = 0;
	//���p�\�ȃQ�[���R���g���[���[�̗񋓊֐������s
	MFAIL(dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumJoysticksCallback, this, DIEDFL_ATTACHEDONLY),
		"���p�\�ȃQ�[���R���g���[���[�̗񋓂Ɏ��s���܂����B");
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		dInputController[i].initialize(_wnd);
		
		if (strcmp(dInputController[i].name, "Controller (Xbox One For Windows)") == 0)
			virtualController[i] = new D_XBOX_ONE_ELITE(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Pro Controller") == 0)
			virtualController[i] = new Nintendo_Switch_Pro_Contoroller(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Wireless Controller") == 0)
			virtualController[i] = new DualShock4(i, &dInputController[i]);
		else
			virtualController[i] = new EMPTY_CONTROLLER();
	}
	//------------------------------------------------

	return S_OK;
}

//===================================================================================================================================
//�y�R���g���[�����̃��Z�b�g�z
//===================================================================================================================================
HRESULT Input::resetController()
{
	//�ēx������
	enumDInputNum = 0;
	//���p�\�ȃQ�[���R���g���[���[�̗񋓊֐������s
	MFAIL(dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumJoysticksCallback, this, DIEDFL_ATTACHEDONLY),
		"���p�\�ȃQ�[���R���g���[���[�̗񋓂Ɏ��s���܂����B");
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		dInputController[i].initialize(wnd);

		if (strcmp(dInputController[i].name, "Controller (Xbox One For Windows)") == 0)
			virtualController[i] = new D_XBOX_ONE_ELITE(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Pro Controller") == 0)
			virtualController[i] = new Nintendo_Switch_Pro_Contoroller(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Wireless Controller") == 0)
			virtualController[i] = new DualShock4(i, &dInputController[i]);
		else
			virtualController[i] = new EMPTY_CONTROLLER();
	}
	return S_OK;
}

//===================================================================================================================================
// ���̃L�[�ɂ��āAkeysDown�z���keysPressed�z���true��ݒ�
// ���s�O�FwParam�ɁA���z�L�[�R�[�h(0�`255)���i�[����Ă���
//===================================================================================================================================
void Input::keyDown(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{// �L�[�R�[�h���A�o�b�t�@�͈͓��ɂ��邱�Ƃ��m�F
		if (keysDown[wParam] == false)
		{
			keysPressed[wParam] = true;
		}
		// keysDown�z����X�V
		keysDown[wParam] = true;
		// keysPressed�z����X�V
	}
}

//===================================================================================================================================
// ���̃L�[�ɂ��āAkeysPressed�z���true��ݒ�
// ���s�O�FwParam�ɁA���z�L�[�R�[�h(0�`255)���i�[����Ă���
//===================================================================================================================================
void Input::keyPress(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{// �L�[�R�[�h���A�o�b�t�@�͈͓��ɂ��邱�Ƃ��m�F

		// keysPressed�z����X�V
		keysPressed[wParam] = true;
	}
}

//===================================================================================================================================
// ���̃L�[�ɂ��āAkeysDown�z���false��ݒ�
// ���s�O�FwParam�ɁA���z�L�[�R�[�h(0�`255)���i�[����Ă���
//===================================================================================================================================
void Input::keyUp(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{// �L�[�R�[�h���A�o�b�t�@�͈͓����邱�Ƃ��m�F
		// ��ԃe�[�u�����X�V
		keysDown[wParam] = false;
	}
}

//===================================================================================================================================
// ���͂��ꂽ������textIn������ɕۑ�
// ���s�O�FwParam�ɁA�������i�[����Ă���
//===================================================================================================================================
void Input::keyIn(WPARAM wParam)
{
	if (newLine)
	{// �V�����s�̊J�n�̏ꍇ
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')
	{// �o�b�N�X�y�[�X�L�[�̏ꍇ
		if (textIn.length() > 0)
		{// ���������݂���ꍇ
			// �Ō�ɓ��͂��ꂽ����������
			textIn.erase(textIn.size() - 1);
		}
	}
	else {
		textIn += wParam;	// ������textIn�ɒǉ�
		charIn = wParam;	// �Ō�ɓ��͂��ꂽ������ۑ�
	}

	if ((char)wParam == '\r')
	{// ���^�[���L�[�̏ꍇ
		newLine = true;		// �V�����s���J�n
	}
}

//===================================================================================================================================
// �w�肳�ꂽ���z�L�[��������Ă���ꍇ��true�A����ȊO�̏ꍇ��false��߂�
//===================================================================================================================================
bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	
	return false;
}

//===================================================================================================================================
// ���߂̃t���[���ɂ����āA�w��̉��z�L�[�������ꂽ���Ƃ�����ꍇ�Atrue��߂��܂��B
// �L�[�̉��������̏�Ԃ́A�e�t���[���̏I�����ɏ�������܂��B
//===================================================================================================================================
bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	return false;
}

//=============================================================================
// ���߂̃t���[���ɂ����āA���炩�̃L�[�������ꂽ�ꍇ�Atrue��߂��܂��B
// �L�[�̉��������̏�Ԃ́A�e�t���[���̏I�����ɏ�������܂��B
//=============================================================================
bool Input::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		if (keysPressed[i] == true)return true;
	}
	return false;
}

//===================================================================================================================================
// �w�肳�ꂽ�L�[�̉����������N���A
//===================================================================================================================================
void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

//===================================================================================================================================
// �w��̓��̓o�b�t�@���N���A
// what�̒l�ɂ��Ă�input.h���Q��
//===================================================================================================================================
void Input::clear(UCHAR what)
{
	// �L�[��������Ă����Ԃ��ǂ������N���A����ꍇ
	if (what & inputNS::KEYS_DOWN)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		{
			keysDown[i] = false;
		}
	}

	// �L�[�������ꂽ���ǂ������N���A����ꍇ
	if (what & inputNS::KEYS_PRESSED)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		{
			keysPressed[i] = false;
		}
	}

	// �}�E�X���N���A����ꍇ
	if (what & inputNS::MOUSE)
	{
		mouseX = 0;
		mouseY = 0;
		mouseRawX = 0;
		mouseRawY = 0;
		zDelta = 0;
		mouseWheelState = inputNS::MOUSE_WHEEL_STATE::NONE;
	}

	if (what & inputNS::TEXT_IN)
	{
		clearTextIn();
	}
}

//===================================================================================================================================
// �}�E�X�̉�ʈʒu��ǂݎ��AmouseX��mouseY�ɕۑ�
//===================================================================================================================================
void Input::mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

//===================================================================================================================================
// �}�E�X����̃��[�f�[�^��ǂݎ��AmouseRawX��mouseRawY�ɕۑ�
// ���̃��[�`���́A�����׃}�E�X�ɑΉ����Ă��܂��B
//===================================================================================================================================
void Input::mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}

//===================================================================================================================================
// �}�E�X�z�C�[���̉�]�ʂ�ǂݎ��ۑ�
//===================================================================================================================================
void Input::mouseWheelIn(WPARAM wParam)
{
	zDelta = GET_WHEEL_DELTA_WPARAM(wParam);//��]��
	//�O��̒[����ǉ�
	zDelta += wheelFraction;

	//�m�b�`�������߂�
	int notch = zDelta / WHEEL_DELTA;

	//�[����ۑ�����
	wheelFraction = zDelta % WHEEL_DELTA;

	if (notch > 0)
	{
		//��ɉ�]�i�`���g�j����
		mouseWheelState = inputNS::MOUSE_WHEEL_STATE::UP;
	}
	else if (notch < 0)
	{
		//���ɉ�]�i�`���g�j����
		mouseWheelState = inputNS::MOUSE_WHEEL_STATE::DOWN;
	}
}

//===================================================================================================================================
//���p�\�ȃW���C�X�e�B�b�N��񋓂���R�[���o�b�N�֐�
//===================================================================================================================================
BOOL CALLBACK Input::enumJoysticksCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
	Input* obj = (Input*)context;
	int num = obj->enumDInputNum;
	if (num > NUM_DINPUT_CONTROLLER)
	{
		obj->enumDInputNum = 0;
		return DIENUM_STOP;
	}
	
	//�����񋓂����ꍇ�A���[�U�[�ɑI���E�m�F������
#ifdef _DEBUG
	TCHAR confirm[MAX_PATH + 1];
	sprintf(confirm, "���̕����f�o�C�X�Ńf�o�C�X�I�u�W�F�N�g���쐬���܂����H\n%s\n%s",
		instance->tszProductName, instance->tszInstanceName);
	if (MessageBox(0, confirm, "�m�F", MB_YESNO) == IDNO)
	{
		return DIENUM_CONTINUE;
	}
#endif // _DEBUG


	//���i����o�^
	sprintf(obj->dInputController[num].name, "%s", instance->tszProductName);

	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	if (FAILED(obj->dinput->CreateDevice(instance->guidInstance, &obj->dInputController[num].device, NULL)))
	{
		return DIENUM_CONTINUE;
	}

	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	obj->dInputController[num].deviceCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(obj->dInputController[num].device->GetCapabilities(&obj->dInputController[num].deviceCaps)))
	{
		//�W���C�X�e�B�b�N�̔\�͂̎擾�Ɏ��s
		SAFE_RELEASE(obj->dInputController[num].device);
		return DIENUM_CONTINUE;//�񋓂𑱂���
	}

	//1�̃C���^�[�t�F�[�X�̎擾�����������̂ŁA���̊i�[��ֈړ�
	obj->enumDInputNum++;

	//���̃f�o�C�X���g��
#if 0
	//�񋓂��I������ꍇ
	return DIENUM_STOP;
#else
	//���̃W���C�X�e�B�b�N���T���i�񋓂���j�ꍇ
	return DIENUM_CONTINUE;
#endif
}

void Input::update(bool windowActivate)
{
	(GetAsyncKeyState(VK_LSHIFT) & 0x8000)?keyDown(VK_LSHIFT):keyUp(VK_LSHIFT);
	(GetAsyncKeyState(VK_RSHIFT) & 0x8000)?keyDown(VK_RSHIFT):keyUp(VK_RSHIFT);
	(GetAsyncKeyState(VK_LCONTROL) & 0x8000)?keyDown(VK_LCONTROL):keyUp(VK_LCONTROL);
	(GetAsyncKeyState(VK_RCONTROL) & 0x8000)?keyDown(VK_RCONTROL):keyUp(VK_RCONTROL);
	(GetAsyncKeyState(VK_LMENU)  & 0x8000)?keyDown(VK_LMENU) :keyUp(VK_LMENU);
	(GetAsyncKeyState(VK_RMENU)  & 0x8000)?keyDown(VK_RMENU) :keyUp(VK_RMENU);
	int connectNum = 0;
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		if (dInputController[i].connected == false)continue;
		dInputController[i].update(windowActivate);
		connectNum++;
	}
	for (int i = 0; i < connectNum; i++)
	{
		virtualController[i]->update();
	}
	updateMouse();
}

//===================================================================================================================================
//�y�}�E�X���̍X�V�z
//===================================================================================================================================
void Input::updateMouse(void)
{
	if (getMouseLButton())
	{
		if (mouseBuffer[0] == false)
		{
			mouseButtonTrigger[0] = true;
			mouseBuffer[0] = true;
		}
		else
		{
			mouseButtonTrigger[0] = false;
		}
	}
	else
	{
		if (mouseBuffer[0] == true)
		{
			mouseButtonTrigger[0] = false;
			mouseBuffer[0] = false;
		}
	}

	if (getMouseMButton())
	{
		if (mouseBuffer[1] == false)
		{
			mouseButtonTrigger[1] = true;
			mouseBuffer[1] = true;
		}
		else
		{
			mouseButtonTrigger[1] = false;
		}
	}
	else
	{
		if (mouseBuffer[1] == true)
		{
			mouseButtonTrigger[1] = false;
			mouseBuffer[1] = false;
		}
	}

	if (getMouseRButton())
	{
		if (mouseBuffer[2] == false)
		{
			mouseButtonTrigger[2] = true;
			mouseBuffer[2] = true;
		}
		else
		{
			mouseButtonTrigger[2] = false;
		}
	}
	else
	{
		if (mouseBuffer[2] == true)
		{
			mouseButtonTrigger[2] = false;
			mouseBuffer[2] = false;
		}
	}
}

//===================================================================================================================================
//�y�C���v�b�g�N���X�擾�֐��z
//===================================================================================================================================
Input* getInput() { return pointerInput; };
