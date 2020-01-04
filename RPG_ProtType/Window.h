//===================================================================================================================================
//�yWindow.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/01
// [�X�V��]2020/01/01
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Base.h"
#include "Input.h"
#include "Icon.h"

//===================================================================================================================================
//�y�萔��`�z
//===================================================================================================================================
#define GetMonitorRect(rc) SystemParametersInfo(SPI_GETWORKAREA,0,rc,0)	//	���j�^�[��`

//===================================================================================================================================
//�y�E�B���h�E�N���X�z
//===================================================================================================================================
class Window : public Base
{
public:
	//Data
	HWND wnd;
	Input* input;
	RECT rect;
	bool windowActivate;
	bool initialized;
	bool fullScreen;
	//Method
	LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);
	Window();
	HRESULT initialize(HINSTANCE, INT, INT, INT, INT, LPSTR);
	void update();
	BOOL setWindowCenter(HWND _windowHandle);
	void changeDisplayMode(bool fullScreen);
	void move(int x, int y);
	//setter
	void setInput();

	//getter
	D3DXVECTOR2 getCenter();
	RECT getRect();

	int windowPositionY = NULL;	//	�E�B���h�E�ʒu Y
	int windowPositionX = NULL;	//	�E�B���h�E�ʒu X
	int windowSizeX = NULL;		//	�E�B���h�E�T�C�Y X
	int windowSizeY = NULL;		//	�E�B���h�E�T�C�Y Y
	int desktopSizeX = NULL;	//	�f�X�N�g�b�v�T�C�Y X
	int desktopSizeY = NULL;	//	�f�X�N�g�b�v�T�C�Y Y
	int clientSizeX = NULL;	//	�N���C�A���g�T�C�Y X
	int clientSizeY = NULL;	//	�N���C�A���g�T�C�Y Y


};