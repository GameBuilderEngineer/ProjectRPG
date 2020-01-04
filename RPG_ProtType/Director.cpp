//===================================================================================================================================
//【Director.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2020/01/01
// [更新日]2020/01/01
//===================================================================================================================================

//===================================================================================================================================
//【インクルード】
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
//【コンストラクタ】
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
//【デストラクタ】
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

	// COMの終了処理
	CoUninitialize();

}

//===================================================================================================================================
//【デバイスの復元】
//===================================================================================================================================
void Director::recoverDevice() {
	HRESULT hr = getDeviceState();
	//MESSAGE("デバイスがロストしました。\n復帰を試みます。", "ERROR:D3DERR_DEVICELOST");
	//デバイスロスト時処理
	if (FAILED(hr))
	{
		if (hr == D3DERR_DEVICENOTRESET)
		{
			//シーン内オブジェクトリソース解放処理
			//※ここに追加 scene->releaseD3DResource();
#ifdef _DEBUG
			imgui->reset();
#endif // _DEBUG

			hr = d3d->resetDevice();
			if (hr == D3D_OK)
			{
				//MESSAGE("デバイスの復帰に成功しました。\nゲームを再開します。", "デバイスの復帰に成功");
				//シーン内オブジェクトリソース再作成
				//※ここに追加 scene->resetD3DResource();
			}
		}
		else {
			Sleep(1000);
		}
	}
}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
HRESULT Director::initialize() {
	//window
	window = new Window;
	if (!window)return E_FAIL;
	MFAIL(window->initialize(instance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME), "ウィンドウ作成失敗");
	wnd = window->wnd;

	//input
	input = new Input();
	input->initialize(instance, window->wnd, true);
	window->setInput();

	//direct3D9
	d3d = new Direct3D9;
	if (d3d == NULL)
	{
		MSG("Direct3Dの初期化失敗");
		return E_FAIL;
	}
	MFAIL(d3d->initialize(wnd), "Direct3D初期化失敗");

#ifdef _DEBUG
	//thread_a = new std::thread(threadA);
	SetForegroundWindow(wnd);
	imgui = new ImguiManager(wnd);
#endif // _DEBUG

	//シリアル通信クラス
	//serialCommunication = new SerialCommunication();

	//エフェクシアー
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

	//メッシュ読み込み
	// Xファイルからメッシュをロードする	
	//StaticMesh
	//staticMeshLoader = new StaticMeshLoader;
	//staticMeshLoader->load(getDevice());

	//シェーダー読込
	//Shader
	//shaderLoader = new ShaderLoader;
	//shaderLoader->load(getDevice());

	//テキストデータ読込
	//textManager = new TextManager();
	//textManager->initialize();

	//ゲーム管理クラス
	//gameMaster = new GameMaster();

	//アニメーション読込クラス
	//animationLoader = new AnimationLoader();
	//animationLoader->initialize(d3d->device);
	//InitMoveP(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.003f, 0.003f, 0.003f), true);
	//InitMoveP1(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.003f, 0.003f, 0.003f), true);

	bool debugMode = false;
#ifdef _DEBUG
	//if (MessageBox(0, "はい(Y):Debugモード\nいいえ(N):次へ", "デバッグシーンへ遷移しますか？", MB_YESNO | MB_TOPMOST) == IDYES)
	//{
	//	scene = new DebugScene();
	//	debugMode = true;
	//}
	//else if (MessageBox(0, "はい(Y):Finaleシーン\nいいえ(N):次へ", "Finaleシーンを確認しますか", MB_YESNO | MB_TOPMOST) == IDYES)
	//{
	//	scene = new Finale();
	//	debugMode = true;
	//}
#endif // _DEBUG

	//scene
	//シーン選択
	//if (debugMode == false)
	//{
	//	if (MessageBox(0, "はい(Y):Gameモード\nいいえ(N):Displayモード", "アプリモード選択", MB_YESNO | MB_TOPMOST) == IDYES)
	//	{
	//		scene = new Splash();
	//		int msg = MessageBox(0,
	//			"はい(Y):接続先を検索\nいいえ(N):インターネット接続を行わない",
	//			"インターネット接続を行いますか?", MB_YESNO | MB_TOPMOST);
	//		if (msg == IDYES)
	//		{
	//			//はい
	//			NETWORK_CLIENT::requestConnection = true;
	//			MSG("接続テストをおこないます。");
	//			NETWORK_CLIENT* test = new NETWORK_CLIENT();
	//			SAFE_DELETE(test);
	//		}
	//		else {
	//			//いいえ
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

	// 高分解能タイマーの準備を試みる
	if (QueryPerformanceFrequency(&timerFreq) == false)
	{
		MSG("高分解能タイマーの取得失敗しました。");
	}
	// 開始時間を取得
	QueryPerformanceCounter(&timeStart);

	// COMの初期化
	CoInitializeEx(NULL, NULL);

	return S_OK;
}


//===================================================================================================================================
//【基本処理】
// [用途]処理の順序の定義
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

	// メッセージループ
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
//【メインループ関数】
// [用途]基本的にループする内容
//===================================================================================================================================
void Director::mainLoop() {

	//入力情報を更新
	input->update(window->windowActivate);

	//リセット
	//if (input->wasKeyPressed(VK_F5))
	//{
	//	scene->changeScene(SceneList::SPLASH);
	//	changeNextScene();
	//}

	//シーン切替フラグの確認
	//if (scene->checkChangeOrder())
	//{
	//	//fader->start();
	//	//if(fader->nowPlaying())//フェードアウトが完了し、フェードアニメ再生中
	//	changeNextScene();
	//}

	if (d3d->deviceLost)
	{
		recoverDevice();
	}
	else
	{
		setFrameTime();				//フレーム時間の初期化処理
		update();					//メイン更新処理
		render();					//メイン描画処理
		fixFPS();					//固定FPS処理
		displayFPS();				//windowネームへFPS表示
	}

	//入力をクリア:すべてのキーチェックが行われた後これを呼び出す
	input->clear(inputNS::MOUSE | inputNS::KEYS_PRESSED);
}

//===================================================================================================================================
//【更新処理】
// [用途]アプリ全体の更新処理
//===================================================================================================================================
void Director::update() {

	//フルスクリーン切替
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
	//ウィンドウ位置/サイズ補正
	if (input->wasKeyPressed(VK_F6))
	{
		window->setWindowCenter(window->wnd);
	}
	//ウィンドウの移動
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
//【GUIウィンドウの作成】
// [用途]GUIウィンドウの作成処理
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
	ImGui::Text("CPU %.2f ％", memory->getCpuUsege());
	ImGui::Text("MEMORY %d kb", memory->getMemoryUsege());
	ImGui::Text("PHYS_MEMORY %d kb", memory->getPhysMemorys());
	ImGui::Text("WindowSize(%d,%d)", window->windowSizeX,window->windowSizeY);
	ImGui::Text("WindowPosition(%d,%d)", window->windowPositionX,window->windowPositionY);
	ImGui::Text("DesktopSize(%d,%d)", window->desktopSizeX,window->desktopSizeY);
	ImGui::Text("ClientSize(%d,%d)", window->clientSizeX,window->clientSizeY);
	

#endif // _DEBUG
}

//===================================================================================================================================
//【描画処理】
// [用途]アプリ全体の描画処理
//===================================================================================================================================
void Director::render() {
	if (d3d->deviceLost)return;
#ifndef _DEBUG
	//描画スキップ
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
//【フレーム時間のセット】
// [用途]フレーム時間の初期設定処理
//===================================================================================================================================
void Director::setFrameTime()
{
	// 最後のフレームからの経過時間を計算、frameTimeに保存
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;
	timeStart = timeEnd;
}

//===================================================================================================================================
//【フレームレート固定処理】
// [用途]FPSを定数により指定した周期に固定する処理
// fpsModeに応じて固定フレームレートか制限なし可変フレームレートに切り替わる
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

		//ここに次フレームまでの待機中にさせたい処理を記述
		if (lockCursor)
		{
			//if (input->getMouseRawX() != 0 || input->getMouseRawY() != 0)
			//	SetCursorPos((int)window->getCenter().x, (int)window->getCenter().y);
		}
	}
	PreviousTime = CurrentTime;
}

//===================================================================================================================================
//【FPS表示処理】
// [用途]FPSをウィンドウネームに表示する処理
//===================================================================================================================================
void Director::displayFPS() {
	//FPS計算表示
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
//【シーン遷移処理】
// [用途]シーンクラスが遷移状態になった場合にシーンを遷移させる処理
//===================================================================================================================================
void Director::changeNextScene() {
	//int nextScene = scene->checkNextScene();		//次のシーンIDを取得	
	//effekseerNS::stop(0);							//全エフェクト停止
	//effekseerNS::stop(1);							//全エフェクト停止
	//effekseerNS::stop(2);							//全エフェクト停止
	//scene->uninitialize();							//シーン終了処理
	//SAFE_DELETE(scene);								// シーンの削除
	//switch (nextScene)								// 指定されたシーンへ遷移
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
	//scene->setGameMaster(gameMaster);				//ゲーム管理情報をシーンへセット
	//scene->initialize();							//シーン初期化処理
	//currentSceneName = scene->getSceneName();		//現在シーン名の取得
}

//void threadA()
//{
//	while (roop)
//	{
//	}
//}