//===================================================================================================================================
//�yDirect3D9.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/01
// [�X�V��]2020/01/01
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Direct3D9.h"

//===================================================================================================================================
//�y�O���[�o���ϐ��z
//===================================================================================================================================
static LPDIRECT3DDEVICE9* pointerDevice = NULL;
static Direct3D9* pointerDirect3D9 = NULL;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
Direct3D9::Direct3D9()
{
	ZeroMemory(this, sizeof(Direct3D9));
	pointerDevice = &this->device;
	pointerDirect3D9 = this;
	fullScreen = false;
	deviceLost = false;
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
Direct3D9::~Direct3D9()
{
	pointerDevice = NULL;
	pointerDirect3D9 = NULL;
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);
}

//===================================================================================================================================
//�yDirect3D�I�u�W�F�N�g���\�[�X�̉���z
//===================================================================================================================================
void Direct3D9::releaseResource()
{
	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(zBuffer);
}

//===================================================================================================================================
//�y�f�o�C�X�X�e�[�g�̐ݒ�z
//===================================================================================================================================
void Direct3D9::resetState()
{
	device->SetRenderState(D3DRS_ZENABLE, true);					//Z�o�b�t�@�[������L���ɂ���
	device->SetRenderState(D3DRS_LIGHTING, true);					//���C�g��L���ɂ���
	device->SetRenderState(D3DRS_AMBIENT, 0x22111111);				//�A���r�G���g���C�g�i�����j��ݒ肷��
	device->SetRenderState(D3DRS_SPECULARENABLE, true);				//�X�y�L�����i���򔽎ˁj��L���ɂ���
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			//�J�����O�̖�����
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//�����v���J�����O�L����
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);			//���v���J�����O�L����
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);		//�A���`�G�C���A�V���O��������
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//���u�����h���s��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//���f�X�e�B�l�[�V�����J���[�̎w��
	device->GetViewport(&viewPort);									//�r���[�|�[�g���擾
	device->GetRenderTarget(0, &backBuffer);						//�o�b�N�o�b�t�@���擾
	device->GetDepthStencilSurface(&zBuffer);						//Z�o�b�t�@���擾
}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
HRESULT Direct3D9::initialize(HWND targetWnd)
{
	//Direct3D�I�u�W�F�N�g�̍쐬
	if (NULL == (d3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MSG("Direct3D�̍쐬�Ɏ��s���܂���");
		return E_FAIL;
	}
	//�f�B�X�v���C���[�h�̎擾
	D3DDISPLAYMODE dMode;
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dMode);

	//--------------------------------------
	//�uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	//--------------------------------------

	//Window���[�h�̃p�����[�^�̍쐬
	ZeroMemory(&d3dppWindow, sizeof(d3dppWindow));
	d3dppWindow.BackBufferWidth					= WINDOW_WIDTH;
	d3dppWindow.BackBufferHeight				= WINDOW_HEIGHT;
	d3dppWindow.BackBufferFormat				= dMode.Format;
	d3dppWindow.BackBufferCount					= 1;
	d3dppWindow.MultiSampleType					= D3DMULTISAMPLE_NONE;
	d3dppWindow.MultiSampleQuality				= 0;
	d3dppWindow.SwapEffect						= D3DSWAPEFFECT_DISCARD;
	d3dppWindow.Windowed						= true;
	d3dppWindow.EnableAutoDepthStencil			= true;
	d3dppWindow.AutoDepthStencilFormat			= D3DFMT_D24S8;
	d3dppWindow.Flags							= 0;
	d3dppWindow.FullScreen_RefreshRateInHz		= 0;
	d3dppWindow.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;

	//FullScreen���[�h�̃p�����[�^�̍쐬
	ZeroMemory(&d3dppFullScreen, sizeof(d3dppFullScreen));
	d3dppFullScreen.BackBufferWidth				= WINDOW_WIDTH;
	d3dppFullScreen.BackBufferHeight			= WINDOW_HEIGHT;
	d3dppFullScreen.BackBufferFormat			= dMode.Format;
	d3dppFullScreen.BackBufferCount				= 1;
	d3dppFullScreen.MultiSampleType				= D3DMULTISAMPLE_NONE;
	d3dppFullScreen.MultiSampleQuality			= 0;
	d3dppFullScreen.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dppFullScreen.Windowed					= false;
	d3dppFullScreen.EnableAutoDepthStencil		= true;
	d3dppFullScreen.AutoDepthStencilFormat		= D3DFMT_D24S8;
	d3dppFullScreen.Flags						= 0;
	d3dppFullScreen.FullScreen_RefreshRateInHz	= dMode.RefreshRate;
	d3dppFullScreen.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;

	//	D3DPRESENT_PARAMETERS d3dpp;
	//	ZeroMemory(&d3dpp, sizeof(d3dpp));
	//	d3dpp.BackBufferFormat			= dMode.Format;
	//	d3dpp.BackBufferCount			= 1;
	//	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	//#ifdef _DEBUG
	//#if 1
	//	d3dpp.Windowed					= true;
	//	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;
	//#else
	//	d3dpp.FullScreen_RefreshRateInHz = dMode.RefreshRate;
	//	d3dpp.Windowed = false;
	//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//#endif
	//#else
	//	d3dpp.FullScreen_RefreshRateInHz = dMode.RefreshRate;
	//	d3dpp.Windowed					= false;
	//	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;
	//#endif // _DEBUG
	//	d3dpp.BackBufferWidth			= WINDOW_WIDTH;
	//	d3dpp.BackBufferHeight			= WINDOW_HEIGHT;
	//	d3dpp.EnableAutoDepthStencil	= true;
	//	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	//	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;

#ifdef _DEBUG
#if 1
	fullScreen = false;
#else
	fullScreen = true;
#endif
#else
	fullScreen = true;
#endif // _DEBUG

	if (fullScreen)
	{
		d3dpp = d3dppFullScreen;
	}
	else {
		d3dpp = d3dppWindow;
	}

	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, targetWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &device)))
	{
		MessageBox(0, "HARDWARE���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nSOFTWARE���[�h�ōĎ��s���܂�", NULL, MB_OK);
		if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, targetWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &device)))
		{
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, targetWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &device)))
			{
				if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, targetWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &device)))
				{
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
	}

	//�X�e�[�g�̐ݒ�
	resetState();

	return S_OK;
}

//===================================================================================================================================
//�yFPS�\�������z
//===================================================================================================================================
void Direct3D9::showFPS()
{
	static INT frames = 0, FPS = 0;
	static LARGE_INTEGER frq = { 0 }, previous = { 0 }, current = { 0 };
	DOUBLE time = 0;
	//char sz[11] = { 0 };

	QueryPerformanceFrequency(&frq);

	QueryPerformanceCounter(&current);
	time = (DOUBLE)(current.QuadPart - previous.QuadPart);
	time *= (DOUBLE)1100.0 / (DOUBLE)frq.QuadPart;
	if (time >= 1100.000)
	{
		previous = current;
		FPS = frames;
		frames = 0;
	}

	frames++;
}

//===================================================================================================================================
//�y��ʃN���A�����z
//===================================================================================================================================
void Direct3D9::clear()
{
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}
void Direct3D9::clear(D3DCOLOR color)
{
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
}

//===================================================================================================================================
//�y��ʍX�V�����z
//===================================================================================================================================
HRESULT Direct3D9::present()
{
	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɂ���j
	HRESULT result = device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST)
	{
		deviceLost = true;
	}

	return result;
}

//===================================================================================================================================
//�y�`��J�n�����z
//===================================================================================================================================
HRESULT Direct3D9::beginScene()
{
	if (device == NULL)return E_FAIL;
	return device->BeginScene();//�`��̂��߂̃V�[�����J�n����
}

//===================================================================================================================================
//�y�`��I�������z
//===================================================================================================================================
HRESULT Direct3D9::endScene()
{
	if (device == NULL)return E_FAIL;
	return device->EndScene();
}

//===================================================================================================================================
//�y�`���ؑ֏����z
//[�ؑ֐�]�E�B���h�E�S��
//===================================================================================================================================
HRESULT Direct3D9::changeViewportFullWindow()
{
	changeViewport(0, 0, viewPort.Width, viewPort.Height);
	return S_OK;
}

//===================================================================================================================================
//�y�`���ؑ֏����z
//[�ؑ֐�]�E�B���h�E����
//===================================================================================================================================
HRESULT Direct3D9::changeViewport1PWindow()
{
	changeViewport(0, 0, viewPort.Width / 2, viewPort.Height);
	return S_OK;
}

//===================================================================================================================================
//�y�`���ؑ֏����z
//[�ؑ֐�]�E�B���h�E�E��
//===================================================================================================================================
HRESULT Direct3D9::changeViewport2PWindow()
{
	changeViewport(viewPort.Width / 2, 0, viewPort.Width / 2, viewPort.Height);
	return S_OK;
}

//===================================================================================================================================
//�y�r���[�|�[�g�ؑ֏����z
//[�p�r]�r���[�|�[�g��؂�ւ��邱�Ƃŕ`����؂�ւ���
//===================================================================================================================================
HRESULT Direct3D9::changeViewport(DWORD x, DWORD y, DWORD width, DWORD height)
{
	D3DVIEWPORT9 vp;

	vp.X = x;
	vp.Y = y;
	vp.Width = width;
	vp.Height = height;
	vp.MinZ = 0;
	vp.MaxZ = 1;


	(device->SetViewport(&vp), "�r���[�|�[�g�؂�ւ����s");

	return S_OK;
}

//===================================================================================================================================
//�y�o�b�N�o�b�t�@�փ����_�[�^�[�Q�b�g����z
//===================================================================================================================================
void Direct3D9::setRenderBackBuffer(DWORD index)
{
	device->SetRenderTarget(index, backBuffer);
	device->SetDepthStencilSurface(zBuffer);
}

//===================================================================================================================================
//�y��ʃ��[�h�ؑցz
//===================================================================================================================================
void Direct3D9::changeDisplayMode(bool fullScreen)
{
	if (this->fullScreen == fullScreen)	return;

	this->fullScreen = fullScreen;

	if (this->fullScreen)
	{
		d3dpp = d3dppFullScreen;
	}
	else {
		d3dpp = d3dppWindow;
	}

	//�f�o�C�X�̃��Z�b�g
	if (resetDevice() == D3D_OK)
	{
		MESSAGE("�f�B�X�v���C���[�h�̐ؑւɐ������܂����B", "�f�B�X�v���C���[�h�ؑ�");
	}
}

//===================================================================================================================================
//�y�f�o�C�X�̃��Z�b�g�z
//===================================================================================================================================
HRESULT Direct3D9::resetDevice()
{
	//Direct3D�I�u�W�F�N�g���\�[�X�̉��
	releaseResource();

	//�f�o�C�X�̃��Z�b�g
	HRESULT hr = device->Reset(&d3dpp);

	if (FAILED(hr))
	{
		if (hr == D3DERR_DEVICELOST)
			return hr;
			//MESSAGE("ERROR_CODE:D3DERR_DEVICELOST", "ERROR:ChangeDisplayMode Reset");

		if (hr == D3DERR_WRONGTEXTUREFORMAT)
			MESSAGE("ERROR_CODE:D3DERR_WRONGTEXTUREFORMAT", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_UNSUPPORTEDCOLOROPERATION)
			MESSAGE("ERROR_CODE:D3DERR_UNSUPPORTEDCOLOROPERATION", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_UNSUPPORTEDCOLORARG)
			MESSAGE("ERROR_CODE:D3DERR_UNSUPPORTEDCOLORARG", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_UNSUPPORTEDALPHAOPERATION)
			MESSAGE("ERROR_CODE:D3DERR_UNSUPPORTEDALPHAOPERATION", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_UNSUPPORTEDALPHAARG)
			MESSAGE("ERROR_CODE:D3DERR_UNSUPPORTEDALPHAARG", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_TOOMANYOPERATIONS)
			MESSAGE("ERROR_CODE:D3DERR_TOOMANYOPERATIONS", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_CONFLICTINGTEXTUREFILTER)
			MESSAGE("ERROR_CODE:D3DERR_CONFLICTINGTEXTUREFILTER", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_UNSUPPORTEDFACTORVALUE)
			MESSAGE("ERROR_CODE:D3DERR_UNSUPPORTEDFACTORVALUE", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_CONFLICTINGRENDERSTATE)
			MESSAGE("ERROR_CODE:D3DERR_CONFLICTINGRENDERSTATE", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_UNSUPPORTEDTEXTUREFILTER)
			MESSAGE("ERROR_CODE:D3DERR_UNSUPPORTEDTEXTUREFILTER", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_CONFLICTINGTEXTUREPALETTE)
			MESSAGE("ERROR_CODE:D3DERR_CONFLICTINGTEXTUREPALETTE", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_DRIVERINTERNALERROR)
			MESSAGE("ERROR_CODE:D3DERR_DRIVERINTERNALERROR", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_NOTFOUND)
			MESSAGE("ERROR_CODE:D3DERR_NOTFOUND", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_MOREDATA)
			MESSAGE("ERROR_CODE:D3DERR_MOREDATA", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_INVALIDDEVICE)
			MESSAGE("ERROR_CODE:D3DERR_INVALIDDEVICE", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_DEVICENOTRESET)
			MESSAGE("ERROR_CODE:D3DERR_DEVICENOTRESET", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_NOTAVAILABLE)
			MESSAGE("ERROR_CODE:D3DERR_NOTAVAILABLE", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_OUTOFVIDEOMEMORY)
			MESSAGE("ERROR_CODE:D3DERR_OUTOFVIDEOMEMORY", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_INVALIDCALL)
			MESSAGE("ERROR_CODE:D3DERR_INVALIDCALL", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_DRIVERINVALIDCALL)
			MESSAGE("ERROR_CODE:D3DERR_DRIVERINVALIDCALL", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DERR_WASSTILLDRAWING)
			MESSAGE("ERROR_CODE:D3DERR_WASSTILLDRAWING", "ERROR:ChangeDisplayMode Reset");
		if (hr == D3DOK_NOAUTOGEN)
			MESSAGE("ERROR_CODE:D3DOK_NOAUTOGEN", "ERROR:ChangeDisplayMode Reset");

		MESSAGE("�f�o�C�X�̃��Z�b�g�Ɏ��s�����̂ŃA�v���P�[�V�������I�����܂�", "ERROR:ChangeDisplayMode Reset");
		PostQuitMessage(0);
	}

	resetState();
	deviceLost = false;
	
	return D3D_OK;
}

//===================================================================================================================================
//�yDirect3D�f�o�C�X������Ԃ̌��m�z
//===================================================================================================================================
HRESULT getDeviceState() { 
	if (pointerDevice == NULL)	return E_FAIL;
	return (*pointerDevice)->TestCooperativeLevel();
}

//===================================================================================================================================
//�yDirect3D�f�o�C�X�擾�֐��z
//===================================================================================================================================
LPDIRECT3DDEVICE9 getDevice() { return *pointerDevice; }

//===================================================================================================================================
//�yDirect3D9�N���X�擾�֐��z
//===================================================================================================================================
Direct3D9* getDirect3D9() { return pointerDirect3D9; }
