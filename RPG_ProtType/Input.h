//===================================================================================================================================
//�yInput.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/01
// [�X�V��]2020/01/01
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Base.h"
#include "DirectInputController.h"
#include "VirtualController.h"
#include <WindowsX.h>

//===================================================================================================================================
//�y�}�N����`�z
//===================================================================================================================================
// �����׃}�E�X�p
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC		((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE		((USHORT) 0x02)
#endif

//===================================================================================================================================
//�y���O��ԁz
//===================================================================================================================================
namespace inputNS
{
	enum {
		DINPUT_1P,
		DINPUT_2P,
		DINPUT_3P,
		DINPUT_4P,
		NUM_DINPUT_CONTROLLER,
	};
	const int KEYS_ARRAY_LEN = 256;		// �L�[�z��̃T�C�Y

	enum MOUSE_WHEEL_STATE {
		NONE,
		UP,
		DOWN,
	};

	// clear()�A�r�b�g�t���O
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

//===================================================================================================================================
//�y���̓N���X�z
//===================================================================================================================================
class Input : public Base
{
private:
	HWND wnd;

	//-----------------------
	//KeyBoard
	//-----------------------
	bool keysDown[inputNS::KEYS_ARRAY_LEN];			// �w�肳�ꂽ�L�[���_�E�����Ă���ꍇ��true
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];		// �w�肳�ꂽ�L�[�������ꂽ�ꍇ��true
	std::string textIn;								// ���[�U�[�����͂����e�L�X�g
	char charIn;									// �Ō�ɓ��͂�������
	bool newLine;									// ���s�̊J�n����true

	//-----------------------
	//Mouse
	//-----------------------
	int mouseRawX, mouseRawY;		// ���𑜓x�̃}�E�X�f�[�^
	int mouseX, mouseY;				// �}�E�X�̉�ʍ��W
	RAWINPUTDEVICE Rid[1];			// �����׃}�E�X�p
	bool mouseCaptured;				// �}�E�X���L���v�`�����ꂽ�ꍇ��true
	bool mouseLButton;				// �}�E�X�̍��{�^����������Ă���ꍇ��true
	bool mouseMButton;				// ���}�E�X�{�^����������Ă���ꍇ��true
	bool mouseRButton;				// �}�E�X�̉E�{�^����������Ă���ꍇ��true
	bool mouseX1Button;				// X1�̃}�E�X�{�^����������Ă���ꍇ��true
	bool mouseX2Button;				// X2�̃}�E�X�{�^����������Ă���ꍇ��true
	bool mouseBuffer[5] = { false,false,false,false,false };
	bool mouseButtonTrigger[5] = { false,false,false,false,false };						// �}�E�X�̃{�^���������ꂽ����x����true,���Ԃ͏㏀��;
	int wheelFraction;				//��]�ʂ̒[��
	int zDelta;						//��]��
	int mouseWheelState;			//��]�����̏�ԕϐ�

	//-----------------------
	//DInputController
	//-----------------------
	LPDIRECTINPUT8 dinput = NULL;												// DirectInput�C���^�[�t�F�[�X
	DirectInputController dInputController[inputNS::NUM_DINPUT_CONTROLLER];		// DirectInput�R���g���[��
	int enumDInputNum;

	//-----------------------
	//���z�R���g���[���C���^�[�t�F�[�X
	//-----------------------
	VirtualController* virtualController[inputNS::NUM_DINPUT_CONTROLLER];

public:
	Input();
	virtual ~Input();
	HRESULT initialize(HINSTANCE instance, HWND _wnd,bool capture);
	void update(bool windowActivate);
	
	void clear(UCHAR what);									// �w�肳�ꂽ���̓o�b�t�@���N���A����B// KEYS_DOWN�AKEYS_PRESSED�AMOUSE�ATEXT_IN�܂���KEYS_MOUSE_TEXT�B// OR '|'���g�p����p�����[�^��g�ݍ��킹��I�y���[�^�B
	void clearAll() { clear(inputNS::KEYS_MOUSE_TEXT); }	// �L�[�A�}�E�X�A����уe�L�X�g���̓f�[�^���N���A���܂��B

	//-----------------------
	//Controller
	//-----------------------
	VirtualController** getController() { return virtualController; };
	HRESULT resetController();

	//-----------------------
	//KeyBoard
	//-----------------------
	void keyDown(WPARAM);									// �L�[�_�E����Ԃ�ۑ�����
	void keyPress(WPARAM);									// �L�[�v���X��Ԃ�ۑ�����
	void keyUp(WPARAM);										// �L�[�A�b�v��Ԃ�ۑ�����
	void keyIn(WPARAM);											// textIn string �ɓ��͂����΂���̕�����ۑ�����
	bool isKeyDown(UCHAR vkey) const;					// �w�肳�ꂽ���z�L�[���_�E�����Ă���ꍇ��true�A�����łȂ��ꍇ��false��Ԃ��܂��B
	bool wasKeyPressed(UCHAR vkey) const;				// �w�肳�ꂽVIRTUAL KEY���Ō�̃t���[���ŉ����ꂽ�ꍇ��true��Ԃ��܂��B// �L�[�̉����́A�e�t���[���̍Ō�ŏ�������܂��B
	bool anyKeyPressed() const;								// ���߂̃t���[���ŃL�[�������ꂽ�ꍇ��true��Ԃ��܂��B// �L�[�̉����́A�e�t���[���̍Ō�ŏ�������܂��B
	void clearKeyPress(UCHAR vkey);						// �w�肳�ꂽ�L�[���N���A����
	void clearTextIn() { textIn.clear(); }					// �N���A�e�L�X�g���̓o�b�t�@
	std::string getTextIn() { return textIn; }				// �e�L�X�g���͂𕶎���Ƃ��ĕԂ�
	char getCharIn() { return charIn; }						// �Ō�ɓ��͂���������Ԃ��܂�

	//-----------------------
	//Mouse
	//-----------------------
	void mouseIn(LPARAM);									// �}�E�X�̈ʒu��mouseX�AmouseY�ɓǂݍ��݂܂�
	void mouseRawIn(LPARAM);								// ���̃}�E�X�f�[�^��mouseRawX�AmouseRawY�ɓǂݍ��݂܂�// ���̃��[�`���͍����׃}�E�X�ƌ݊���������܂�
	void mouseWheelIn(WPARAM wParam);						// �}�E�X�̉�]�ʂ�ۑ�
	void clearWheelFraction() { wheelFraction = 0; };		// �E�B���h�E�̃A�N�e�B�u�؂�ւ����ɒ[�������Z�b�g
	void setMouseLButton(bool b) { mouseLButton = b; }		// ���}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseMButton(bool b) { mouseMButton = b; }		// �����}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseRButton(bool b) { mouseRButton = b; }		// �E�}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseXButton(WPARAM wParam) {mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;}	// X�}�E�X�{�^���̏�Ԃ�ۑ�
	int getMouseX()		const { return mouseX; }			// �}�E�X��X�ʒu��߂�
	int getMouseY()		const { return mouseY; }			// �}�E�X��Y�ʒu��߂�
	int getMouseRawX()	const { return mouseRawX; }			// �}�E�X��X�ʒu�̈ړ��̃��[�f�[�^��߂��B���ւ̈ړ���<0�A�E�ւ̈ړ���>0//�����׃}�E�X�ƌ݊���������܂��B
	int getMouseRawY()	const { return mouseRawY; }			// �}�E�X��Y�ʒu�̈ړ��̃��[�f�[�^��߂��B���ւ̈ړ���<0�A�E�ւ̈ړ���>0// �����׃}�E�X�ƌ݊���������܂��B
	int getMouseWheelState() { return mouseWheelState; };
	bool getMouseLButton()	const { return mouseLButton; }	// ���}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseLButtonTrigger() { return mouseButtonTrigger[0]; }	// ���}�E�X�{�^���̃g���K�[����߂�
	bool getMouseMButton()	const { return mouseMButton; }	// �����}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseMButtonTrigger() { return mouseButtonTrigger[1]; }// �����}�E�X�{�^���̃g���K�[����߂�
	bool getMouseRButton()	const { return mouseRButton; }	// �E�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseRButtonTrigger() { return mouseButtonTrigger[2]; }	// �E�}�E�X�{�^���̃g���K�[����߂�
	bool getMouseX1Button()	const { return mouseX1Button; }	// X1�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseX1ButtonTrigger() { return mouseButtonTrigger[3]; }	// X1�}�E�X�{�^���̃g���K�[����߂�
	bool getMouseX2Button()	const { return mouseX2Button; }	// X2�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseX2ButtonTrigger() { return mouseButtonTrigger[4]; }	// X2�}�E�X�{�^���̃g���K�[����߂�
	void updateMouse();

	//-----------------------
	//DInputController
	//-----------------------
	static BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);

};


//===================================================================================================================================
//�y�v���g�^�C�v�錾�z
//===================================================================================================================================
//�C���v�b�g�N���X�擾�֐�
extern Input* getInput();
