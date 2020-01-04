//===================================================================================================================================
//�yDirect3D9.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/01
// [�X�V��]2020/01/01
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Base.h"

//===================================================================================================================================
//�yDirect3D9�N���X�z
//===================================================================================================================================
class Direct3D9 :public Base
{
public:
	//Data
	HWND					wnd;
	LPDIRECT3D9				d3d;
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DPRESENT_PARAMETERS	d3dppWindow;
	D3DPRESENT_PARAMETERS	d3dppFullScreen;
	D3DVIEWPORT9			viewPort;
	LPDIRECT3DDEVICE9		device;
	LPDIRECT3DSURFACE9		backBuffer;		//�o�b�N�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DSURFACE9		zBuffer;
	bool					fullScreen;
	bool					deviceLost;
public:
	//Method
	Direct3D9();
	~Direct3D9();
	void releaseResource();
	HRESULT resetDevice();
	void resetState();
	HRESULT initialize(HWND targetWnd);
	void showFPS();
	void clear();
	void clear(D3DCOLOR color);
	HRESULT present();
	HRESULT beginScene();
	HRESULT endScene();
	HRESULT changeViewport(DWORD x, DWORD y, DWORD width, DWORD height);
	HRESULT changeViewportFullWindow();
	HRESULT changeViewport1PWindow();
	HRESULT changeViewport2PWindow();
	void setRenderBackBuffer(DWORD index);
	void changeDisplayMode(bool fullScreen);
};

//===================================================================================================================================
//�y�v���g�^�C�v�錾�z
//===================================================================================================================================
//Direct3D�f�o�C�X�擾�֐�
extern HRESULT getDeviceState();
//Direct3D�f�o�C�X�擾�֐�
extern LPDIRECT3DDEVICE9 getDevice();
//Direct3D9�N���X�擾�֐�
extern Direct3D9* getDirect3D9();
