//===================================================================================================================================
//【Window.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2020/01/01
// [更新日]2020/01/01
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//【インクルード】
//===================================================================================================================================
#include "Base.h"
#include "Input.h"
#include "Icon.h"

//===================================================================================================================================
//【定数定義】
//===================================================================================================================================
#define GetMonitorRect(rc) SystemParametersInfo(SPI_GETWORKAREA,0,rc,0)	//	モニター矩形

//===================================================================================================================================
//【ウィンドウクラス】
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

	int windowPositionY = NULL;	//	ウィンドウ位置 Y
	int windowPositionX = NULL;	//	ウィンドウ位置 X
	int windowSizeX = NULL;		//	ウィンドウサイズ X
	int windowSizeY = NULL;		//	ウィンドウサイズ Y
	int desktopSizeX = NULL;	//	デスクトップサイズ X
	int desktopSizeY = NULL;	//	デスクトップサイズ Y
	int clientSizeX = NULL;	//	クライアントサイズ X
	int clientSizeY = NULL;	//	クライアントサイズ Y


};