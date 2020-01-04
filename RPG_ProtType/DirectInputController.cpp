//===================================================================================================================================
//�yDirectInputController.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/19
// [�X�V��]2019/09/19
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "DirectInputController.h"

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
HRESULT DirectInputController::initialize(HWND wnd)
{
	connected = false;

	if (device == NULL)return E_FAIL;

	// �f�o�C�X���W���C�X�e�B�b�N�ɐݒ�
	MFAIL(device->SetDataFormat(&c_dfDIJoystick2), "�W���C�X�e�B�b�N�̐ݒ�Ɏ��s���܂����B");

	// �������x���̐ݒ�
	MFAIL(device->SetCooperativeLevel(wnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND),"�������x���̐ݒ�Ɏ��s���܂����B");

	//�A�v���P�[�V�����Ŏg�p����R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��
	MFAIL(device->EnumObjects(EnumObjectsCallback, this, DIDFT_AXIS),"�R���g���[���v���p�e�B�̗񋓂Ɛݒ�Ɏ��s���܂����B");
	
	// �����[�h��ݒ�i��Βl���[�h�ɐݒ�B�f�t�H���g�Ȃ̂ŕK�������ݒ�͕K�v�Ȃ��j
	DIPROPDWORD propWord;
	propWord.diph.dwSize = sizeof(propWord);
	propWord.diph.dwHeaderSize = sizeof(propWord.diph);
	propWord.diph.dwObj = 0;
	propWord.diph.dwHow = DIPH_DEVICE;
	propWord.dwData = DIPROPAXISMODE_ABS;
	//diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�̏ꍇ
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &propWord.diph)))
	{
		MSG("�����[�h�̐ݒ�Ɏ��s");
		return E_FAIL;
	}

	// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
	propWord.dwData = DIDEVICE_BUFFERSIZE;
	if (FAILED(device->SetProperty(DIPROP_BUFFERSIZE, &propWord.diph)))
	{
		MSG("�o�b�t�@�E�T�C�Y�̐ݒ�Ɏ��s");
		return E_FAIL;
	}

	// ���͐���J�n
	connected = true;
	device->Acquire();
	return S_OK;
}

//===================================================================================================================================
//�y�A�v���P�[�V�����Ŏg�p����R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��z�F�R�[���o�b�N�֐�
//===================================================================================================================================
BOOL CALLBACK DirectInputController::EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE objectInstance, VOID* context)
{
	DirectInputController* obj = (DirectInputController*)context;

	DIPROPRANGE propRange;//���͈�
	ZeroMemory(&propRange, sizeof(propRange));
	propRange.diph.dwSize = sizeof(propRange);
	propRange.diph.dwHeaderSize = sizeof(propRange.diph);
	propRange.diph.dwHow = DIPH_BYID;
	propRange.diph.dwObj = objectInstance->dwType;
	propRange.lMin = -1000;
	propRange.lMax = +1000;

	if (FAILED(obj->device->SetProperty(DIPROP_RANGE, &propRange.diph)))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void DirectInputController::update(bool windowActivate)
{
	if (device == NULL)	return;

	HRESULT hr;
	// �f�o�C�X�̒��ڃf�[�^���擾����
	hr = device->Poll();
	if (FAILED(hr))
	{
		hr = device->Acquire();
		while (windowActivate && hr == DIERR_INPUTLOST)
		{
			hr = device->Acquire();
		}
	}

	// �R���g���[���[�̏�Ԃ��擾����
	hr = device->GetDeviceState(sizeof(DIJOYSTATE2), &joyState);
	if (FAILED(hr))
	{
		if (windowActivate && hr == DIERR_INPUTLOST)
		{
			device->Acquire();
		}
	}

	// �o�b�t�@�����O�f�[�^���擾����
	while (windowActivate)
	{
		DWORD items = 1;
		hr = device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &objectData, &items, 0);
		if (hr == DIERR_INPUTLOST)
		{
			device->Acquire();
		}
		else if (FAILED(hr) || items == 0)
		{
			break;// �f�[�^���ǂ߂Ȃ����A���݂��Ȃ�
		}
	}

}