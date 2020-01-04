//===================================================================================================================================
//�yDirector.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/01
// [�X�V��]2020/01/01
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Director.h"
//#include "Splash.h"
//#include "Title.h"
//#include "Tutorial.h"
//#if _DEBUG
//#include "Create.h"
//#endif
//#include "Game.h"
//#include "Result.h"
//#include "Credit.h"
//#include "Display.h"
//#include "Finale.h"
//#include "SE.h"
//#include "LinearTreeCell.h"
//#include "DebugScene.h"
//#include "networkClient.h"
//#include "TreeManager.h"

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
Director::Director() {
	ZeroMemory(this, sizeof(Director));
	fpsMode = FIXED_FPS;
	fixedFps = FRAME_RATE;
#ifdef _DEBUG
	onGUI = true;
	memory = new MemoryViewer;
	hiddenCursor = false;
	lockCursor = false;
	ShowCursor(FALSE);
	ShowCursor(TRUE); 
#else
	hiddenCursor = true;
	lockCursor = true;
	ShowCursor(FALSE);
#endif // _DEBUG
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
Director::~Director() {
	SAFE_DELETE(window);
	SAFE_DELETE(d3d);
#ifdef _DEBUG
	SAFE_DELETE(imgui);
	SAFE_DELETE(memory);
#else
	ShowCursor(TRUE);
#endif // _DEBUG
	SAFE_DELETE(input);
	//SAFE_DELETE(scene);
	//SAFE_DELETE(textureLoader);
	//SAFE_DELETE(staticMeshLoader);
	//SAFE_DELETE(shaderLoader);
	//SAFE_DELETE(soundInterface);
	//SAFE_DELETE(textManager);
	//SAFE_DELETE(fader);
	//SAFE_DELETE(effekseerManager[0]);
	//SAFE_DELETE(effekseerManager[1]);
	//SAFE_DELETE(effekseerManager[2]);
	//SAFE_DELETE(gameMaster);
	//SAFE_DELETE(serialCommunication);
	//SAFE_DELETE(animationLoader);
	//thread_a->join();
	//SAFE_DELETE(thread_a);

	// COM�̏I������
	CoUninitialize();

}

//===================================================================================================================================
//�y�f�o�C�X�̕����z
//===================================================================================================================================
void Director::recoverDevice() {
	HRESULT hr = getDeviceState();
	//MESSAGE("�f�o�C�X�����X�g���܂����B\n���A�����݂܂��B", "ERROR:D3DERR_DEVICELOST");
	//�f�o�C�X���X�g������
	if (FAILED(hr))
	{
		if (hr == D3DERR_DEVICENOTRESET)
		{
			//�V�[�����I�u�W�F�N�g���\�[�X�������
			//�������ɒǉ� scene->releaseD3DResource();
#ifdef _DEBUG
			imgui->reset();
#endif // _DEBUG

			hr = d3d->resetDevice();
			if (hr == D3D_OK)
			{
				//MESSAGE("�f�o�C�X�̕��A�ɐ������܂����B\n�Q�[�����ĊJ���܂��B", "�f�o�C�X�̕��A�ɐ���");
				//�V�[�����I�u�W�F�N�g���\�[�X�č쐬
				//�������ɒǉ� scene->resetD3DResource();
			}
		}
		else {
			Sleep(1000);
		}
	}
}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
HRESULT Director::initialize() {
	//window
	window = new Window;
	if (!window)return E_FAIL;
	MFAIL(window->initialize(instance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME), "�E�B���h�E�쐬���s");
	wnd = window->wnd;

	//input
	input = new Input();
	input->initialize(instance, window->wnd, true);
	window->setInput();

	//direct3D9
	d3d = new Direct3D9;
	if (d3d == NULL)
	{
		MSG("Direct3D�̏��������s");
		return E_FAIL;
	}
	MFAIL(d3d->initialize(wnd), "Direct3D���������s");

#ifdef _DEBUG
	//thread_a = new std::thread(threadA);
	SetForegroundWindow(wnd);
	imgui = new ImguiManager(wnd);
#endif // _DEBUG

	//�V���A���ʐM�N���X
	//serialCommunication = new SerialCommunication();

	//�G�t�F�N�V�A�[
	//effekseerManager[0] = new EffekseerManager();
	//effekseerManager[0]->initialize();
	//effekseerManager[1] = new EffekseerManager();
	//effekseerManager[1]->initialize();
	//effekseerManager[2] = new EffekseerManager();
	//effekseerManager[2]->initialize();

	//sound
	//soundInterface = new SoundInterface();

	//textureLoader
	//textureLoader = new TextureLoader;
	//textureLoader->load(getDevice());

	//���b�V���ǂݍ���
	// X�t�@�C�����烁�b�V�������[�h����	
	//StaticMesh
	//staticMeshLoader = new StaticMeshLoader;
	//staticMeshLoader->load(getDevice());

	//�V�F�[�_�[�Ǎ�
	//Shader
	//shaderLoader = new ShaderLoader;
	//shaderLoader->load(getDevice());

	//�e�L�X�g�f�[�^�Ǎ�
	//textManager = new TextManager();
	//textManager->initialize();

	//�Q�[���Ǘ��N���X
	//gameMaster = new GameMaster();

	//�A�j���[�V�����Ǎ��N���X
	//animationLoader = new AnimationLoader();
	//animationLoader->initialize(d3d->device);
	//InitMoveP(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.003f, 0.003f, 0.003f), true);
	//InitMoveP1(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.003f, 0.003f, 0.003f), true);

	bool debugMode = false;
#ifdef _DEBUG
	//if (MessageBox(0, "�͂�(Y):Debug���[�h\n������(N):����", "�f�o�b�O�V�[���֑J�ڂ��܂����H", MB_YESNO | MB_TOPMOST) == IDYES)
	//{
	//	scene = new DebugScene();
	//	debugMode = true;
	//}
	//else if (MessageBox(0, "�͂�(Y):Finale�V�[��\n������(N):����", "Finale�V�[�����m�F���܂���", MB_YESNO | MB_TOPMOST) == IDYES)
	//{
	//	scene = new Finale();
	//	debugMode = true;
	//}
#endif // _DEBUG

	//scene
	//�V�[���I��
	//if (debugMode == false)
	//{
	//	if (MessageBox(0, "�͂�(Y):Game���[�h\n������(N):Display���[�h", "�A�v�����[�h�I��", MB_YESNO | MB_TOPMOST) == IDYES)
	//	{
	//		scene = new Splash();
	//		int msg = MessageBox(0,
	//			"�͂�(Y):�ڑ��������\n������(N):�C���^�[�l�b�g�ڑ����s��Ȃ�",
	//			"�C���^�[�l�b�g�ڑ����s���܂���?", MB_YESNO | MB_TOPMOST);
	//		if (msg == IDYES)
	//		{
	//			//�͂�
	//			NETWORK_CLIENT::requestConnection = true;
	//			MSG("�ڑ��e�X�g�������Ȃ��܂��B");
	//			NETWORK_CLIENT* test = new NETWORK_CLIENT();
	//			SAFE_DELETE(test);
	//		}
	//		else {
	//			//������
	//			NETWORK_CLIENT::requestConnection = false;
	//		}
	//	}
	//	else {
	//		scene = new Display();
	//	}
	//}

	//scene->setGameMaster(gameMaster);
	//scene->initialize();

	//fader
	//fader = new Fader();
	//fader->setShader(faderNS::BLUR);

#pragma endregion

	// ������\�^�C�}�[�̏��������݂�
	if (QueryPerformanceFrequency(&timerFreq) == false)
	{
		MSG("������\�^�C�}�[�̎擾���s���܂����B");
	}
	// �J�n���Ԃ��擾
	QueryPerformanceCounter(&timeStart);

	// COM�̏�����
	CoInitializeEx(NULL, NULL);

	return S_OK;
}


//===================================================================================================================================
//�y��{�����z
// [�p�r]�����̏����̒�`
//===================================================================================================================================
void Director::run(HINSTANCE _instance) {
	char directory[512];
	GetCurrentDirectory(sizeof(directory), directory);
	initializeDirectory(directory);

	instance = _instance;
	if (FAILED(initialize()))
	{
		return;
	}
	ShowWindow(wnd, SW_SHOW);
	UpdateWindow(wnd);

	// ���b�Z�[�W���[�v
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mainLoop();
		}
	}

}

//===================================================================================================================================
//�y���C�����[�v�֐��z
// [�p�r]��{�I�Ƀ��[�v������e
//===================================================================================================================================
void Director::mainLoop() {

	//���͏����X�V
	input->update(window->windowActivate);

	//���Z�b�g
	//if (input->wasKeyPressed(VK_F5))
	//{
	//	scene->changeScene(SceneList::SPLASH);
	//	changeNextScene();
	//}

	//�V�[���ؑփt���O�̊m�F
	//if (scene->checkChangeOrder())
	//{
	//	//fader->start();
	//	//if(fader->nowPlaying())//�t�F�[�h�A�E�g���������A�t�F�[�h�A�j���Đ���
	//	changeNextScene();
	//}

	if (d3d->deviceLost)
	{
		recoverDevice();
	}
	else
	{
		setFrameTime();				//�t���[�����Ԃ̏���������
		update();					//���C���X�V����
		render();					//���C���`�揈��
		fixFPS();					//�Œ�FPS����
		displayFPS();				//window�l�[����FPS�\��
	}

	//���͂��N���A:���ׂẴL�[�`�F�b�N���s��ꂽ�ケ����Ăяo��
	input->clear(inputNS::MOUSE | inputNS::KEYS_PRESSED);
}

//===================================================================================================================================
//�y�X�V�����z
// [�p�r]�A�v���S�̂̍X�V����
//===================================================================================================================================
void Director::update() {

	//�t���X�N���[���ؑ�
	if (input->isKeyDown(VK_LMENU) && input->wasKeyPressed(VK_RETURN))
	{
		bool fullScreen = !d3d->fullScreen;
#ifdef _DEBUG
		imgui->reset();
#endif // _DEBUG
		d3d->changeDisplayMode(fullScreen);
		window->changeDisplayMode(fullScreen);
		window->setWindowCenter(window->wnd);
	}
	//�E�B���h�E�ʒu/�T�C�Y�␳
	if (input->wasKeyPressed(VK_F6))
	{
		window->setWindowCenter(window->wnd);
	}
	//�E�B���h�E�̈ړ�
	if (input->isKeyDown(VK_LMENU))
	{
		bool onMoveWindow = false;
		int x = 0;
		int y = 0;
		if (input->wasKeyPressed(VK_RIGHT))	x += 1;
		if (input->wasKeyPressed(VK_LEFT))	x -= 1;
		if (input->wasKeyPressed(VK_DOWN))	y += 1;
		if (input->wasKeyPressed(VK_UP))	y -= 1;
		if (input->isKeyDown(VK_LCONTROL))
		{
			x *= 10;
			y *= 10;
		}
		if (x != 0 || y != 0)
		{
			window->move(x, y);
		}
	}
#ifdef _DEBUG
	memory->update();
	imgui->beginFrame();
	imgui->beginImGui("DirectorGUI");
	createGUI();
	imgui->endImGui();
	//if (input->wasKeyPressed(VK_F1))
	//{
	//	hiddenCursor = !hiddenCursor;
	//	if (hiddenCursor) {
	//		ShowCursor(FALSE);
	//	}
	//	else {
	//		ShowCursor(TRUE);
	//	}
	//}
	//if (input->wasKeyPressed(VK_F2))
	//	lockCursor = !lockCursor;
	//if (lockCursor)
	//{
	//	if (input->getMouseRawX() != 0 || input->getMouseRawY() != 0)
	//	{
	//		SetCursorPos((int)window->getCenter().x, (int)window->getCenter().y);
	//	}
	//}
#else
	//if (input->wasKeyPressed(VK_F1))
	//{
	//	hiddenCursor = !hiddenCursor;
	//	if (hiddenCursor) {
	//		ShowCursor(FALSE);
	//	}
	//	else {
	//		ShowCursor(TRUE);
	//	}
	//}
	//if (input->wasKeyPressed(VK_F2))
	//	lockCursor = !lockCursor;
	//if (lockCursor)
	//{
	//	if (input->getMouseRawX() != 0 || input->getMouseRawY() != 0)
	//	{
	//		SetCursorPos((int)window->getCenter().x, (int)window->getCenter().y);
	//	}
	//}
#endif // _DEBUG
	//effekseerManager[0]->update();
	//effekseerManager[1]->update();
	//effekseerManager[2]->update();
	//fader->update(frameTime);
	//scene->update(frameTime);
	//scene->collisions();
	//scene->AI();
	//soundInterface->UpdateSound();
#ifdef _DEBUG
	//if (*scene->getShowGUI())
	//{
	//	imgui->beginImGui(scene->getSceneName()->c_str());
	//	scene->createGUI();
	//	imgui->endImGui();
	//}
	//if (*gameMaster->getShowGUI())
	//{
	//	imgui->beginImGui("GameMasterGUI");
	//	gameMaster->createGUI();
	//	imgui->endImGui();
	//}
	//if (*fader->getShowGUI())
	//{
	//	imgui->beginImGui("FaderGUI");
	//	fader->outputGUI();
	//	imgui->endImGui();
	//}
#endif // _DEBUG
}

//===================================================================================================================================
//�yGUI�E�B���h�E�̍쐬�z
// [�p�r]GUI�E�B���h�E�̍쐬����
//===================================================================================================================================
void Director::createGUI()
{
#ifdef _DEBUG
	if (!onGUI)return;
	ImGui::SliderInt("fpsMode", &fpsMode, VARIABLE_FPS, FIXED_FPS);
	ImGui::SliderInt("fixedFPS", &fixedFps, MIN_FRAME_RATE, MAX_FRAME_RATE);
	ImGui::ColorEdit3("clear color", (float*)&imgui->clearColor);
	//ImGui::Checkbox("SceneGUI", scene->getShowGUI());	
	//ImGui::Checkbox("gameMasterGUI", gameMaster->getShowGUI());	
	//ImGui::Checkbox("faderGUI", fader->getShowGUI());	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("CPU %.2f ��", memory->getCpuUsege());
	ImGui::Text("MEMORY %d kb", memory->getMemoryUsege());
	ImGui::Text("PHYS_MEMORY %d kb", memory->getPhysMemorys());
	ImGui::Text("WindowSize(%d,%d)", window->windowSizeX,window->windowSizeY);
	ImGui::Text("WindowPosition(%d,%d)", window->windowPositionX,window->windowPositionY);
	ImGui::Text("DesktopSize(%d,%d)", window->desktopSizeX,window->desktopSizeY);
	ImGui::Text("ClientSize(%d,%d)", window->clientSizeX,window->clientSizeY);
	

#endif // _DEBUG
}

//===================================================================================================================================
//�y�`�揈���z
// [�p�r]�A�v���S�̂̕`�揈��
//===================================================================================================================================
void Director::render() {
	if (d3d->deviceLost)return;
#ifndef _DEBUG
	//�`��X�L�b�v
	//sleepRenderTime += frameTime;
	//if (sleepRenderTime < 1.000f / ((float)fixedFps * 5 / 6))return;
	//sleepRenderTime = 0.0f;
#endif // !_DEBUG

#ifdef _DEBUG
	//Debug
	if (SUCCEEDED(d3d->beginScene()))
	{
		//if (fader->nowProcessing())
		//{
		//
		//	fader->setRenderTexture();
		//	d3d->clear(imgui->getClearColor());
		//	scene->render();
		//
		//	d3d->setRenderBackBuffer(0);
		//	d3d->clear(imgui->getClearColor());
		//	fader->render();
		//}
		//else
		{
			d3d->clear(imgui->getClearColor());
			d3d->setRenderBackBuffer(0);
			//scene->render();
		}
		imgui->render();

		d3d->endScene();
	}
#else
	//Release
	if (SUCCEEDED(d3d->beginScene()))
	{
		//if (fader->nowProcessing())
		//{
		//	fader->setRenderTexture();
		//	d3d->clear();
		//	scene->render();
		//
		//	d3d->setRenderBackBuffer(0);
		//	d3d->clear();
		//	fader->render();
		//}
		//else
		{
			d3d->clear();
			d3d->setRenderBackBuffer(0);
			//scene->render();
		}
		d3d->endScene();
	}
#endif // _DEBUG
	d3d->present();

}

//===================================================================================================================================
//�y�t���[�����Ԃ̃Z�b�g�z
// [�p�r]�t���[�����Ԃ̏����ݒ菈��
//===================================================================================================================================
void Director::setFrameTime()
{
	// �Ō�̃t���[������̌o�ߎ��Ԃ��v�Z�AframeTime�ɕۑ�
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;
	timeStart = timeEnd;
}

//===================================================================================================================================
//�y�t���[�����[�g�Œ菈���z
// [�p�r]FPS��萔�ɂ��w�肵�������ɌŒ肷�鏈��
// fpsMode�ɉ����ČŒ�t���[�����[�g�������Ȃ��σt���[�����[�g�ɐ؂�ւ��
//===================================================================================================================================
void Director::fixFPS() {
	if (fpsMode != FIXED_FPS)return;
	static INT Frames = 0, FPS = 0;
	static LARGE_INTEGER Frq = { 0 }, PreviousTime = { 0 }, CurrentTime = { 0 };
	DOUBLE Time = 0;
	char sz[11] = { 0 };

	while (Time <= (double)1000/(double)fixedFps)//1000ms / 60frame=16.6666 
	{
		QueryPerformanceFrequency(&Frq);

		QueryPerformanceCounter(&CurrentTime);
		Time = (DOUBLE)(CurrentTime.QuadPart - PreviousTime.QuadPart);

		Time *= (DOUBLE)1000.0 / (DOUBLE)Frq.QuadPart;

		//�����Ɏ��t���[���܂ł̑ҋ@���ɂ��������������L�q
		if (lockCursor)
		{
			//if (input->getMouseRawX() != 0 || input->getMouseRawY() != 0)
			//	SetCursorPos((int)window->getCenter().x, (int)window->getCenter().y);
		}
	}
	PreviousTime = CurrentTime;
}

//===================================================================================================================================
//�yFPS�\�������z
// [�p�r]FPS���E�B���h�E�l�[���ɕ\�����鏈��
//===================================================================================================================================
void Director::displayFPS() {
	//FPS�v�Z�\��
	static LARGE_INTEGER time;
	LARGE_INTEGER time2, frq;
	double elaptime = 0;
	static int frame = 0;
	QueryPerformanceFrequency(&frq);
	double microsec = 1000000 / (double)frq.QuadPart;

	frame++;

	QueryPerformanceCounter(&time2);
	elaptime = (time2.QuadPart - time.QuadPart)*microsec;

	if (elaptime > 1000000)
	{
		QueryPerformanceCounter(&time);

		char str[50];
		char name[200] = { 0 };
		GetClassNameA(wnd, name, sizeof(name));
		sprintf(str, " fps=%d", frame);
		strcat(name, str);
		SetWindowTextA(wnd, name);
		frame = 0;
	}
}

//===================================================================================================================================
//�y�V�[���J�ڏ����z
// [�p�r]�V�[���N���X���J�ڏ�ԂɂȂ����ꍇ�ɃV�[����J�ڂ����鏈��
//===================================================================================================================================
void Director::changeNextScene() {
	//int nextScene = scene->checkNextScene();		//���̃V�[��ID���擾	
	//effekseerNS::stop(0);							//�S�G�t�F�N�g��~
	//effekseerNS::stop(1);							//�S�G�t�F�N�g��~
	//effekseerNS::stop(2);							//�S�G�t�F�N�g��~
	//scene->uninitialize();							//�V�[���I������
	//SAFE_DELETE(scene);								// �V�[���̍폜
	//switch (nextScene)								// �w�肳�ꂽ�V�[���֑J��
	//{
	//case SceneList::DEBUG:					scene = new DebugScene(); break;
	//case SceneList::SPLASH:					scene = new Splash();	break;
	//case SceneList::TITLE:					scene = new Title();		break;
	//case SceneList::TUTORIAL:				scene = new Tutorial(); break;
	//case SceneList::CREDIT:					scene = new Credit();	break;
	//case SceneList::GAME:					scene = new Game();		break;
	//case SceneList::RESULT:					scene = new Result();	break;
	//case SceneList::FINALE:					scene = new Finale();	break;
#if _DEBUG 
	//case SceneList::CREATE:					scene = new Create();	break; 
#endif
	//case SceneList::DISPLAY:				scene = new Display();	break;
	//case SceneList::NONE_SCENE:				break;
	//}
	//scene->setGameMaster(gameMaster);				//�Q�[���Ǘ������V�[���փZ�b�g
	//scene->initialize();							//�V�[������������
	//currentSceneName = scene->getSceneName();		//���݃V�[�����̎擾
}

//void threadA()
//{
//	while (roop)
//	{
//	}
//}