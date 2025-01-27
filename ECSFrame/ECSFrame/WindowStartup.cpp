/**
* @file   WindowStartup.cpp.
* @brief  ウィンドウループ.
* @author Hara Sota.
* @date   2024/10/14.
*/

#define _CRTDBG_MAP_ALLOC
//#define NOMINMAX
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include "Main.h"
#include <stdio.h>
#include <crtdbg.h>
#include <windowsx.h>

#include "imgui_impl_win32.h"

#include "Defines.h"

#pragma comment(lib, "winmm.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc(9389);

	// COMオブジェクト初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		MessageBox(NULL, "COMの初期化に失敗しました。", "error", MB_OK);
		return -1;
	}

	WNDCLASSEX wcex;
	HWND hWnd;
	MSG message;

	// ウィンドウクラス設定
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.hInstance = hInstance;
	wcex.lpszClassName = "Class Name";
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_CLASSDC | CS_DBLCLKS;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// ウィンドウクラス登録
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	// ウィンドウ作成
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	DWORD style = WS_CAPTION | WS_SYSMENU;
	DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&rect, style, false, exStyle);
	hWnd = CreateWindowEx(
		exStyle, wcex.lpszClassName,
		APP_TITLE, style,
		0,0,
		rect.right - rect.left, rect.bottom - rect.top,	// ウィンドウサイズ
		HWND_DESKTOP,
		NULL, hInstance, NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (FAILED(HaraProject::Framework::Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT)))
	{
		HaraProject::Framework::Uninit();
		UnregisterClass(wcex.lpszClassName, hInstance);
		return 0;
	}

	timeBeginPeriod(1);
	DWORD countStartTime = timeGetTime();
	DWORD preExecTime = countStartTime;

	// ウィンドウ管理
	while (1)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&message, NULL, 0, 0))
			{
				break;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			DWORD nowTime = timeGetTime();
			float diff = static_cast<float>(nowTime - preExecTime);
			if (diff >= 1000.0f / 60)
			{
				HaraProject::Framework::Update(diff * 0.001f);
				HaraProject::Framework::Draw();
				preExecTime = nowTime;
			}
		}
	}

	timeEndPeriod(1);
	HaraProject::Framework::Uninit();
	UnregisterClass(wcex.lpszClassName, hInstance);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
#endif
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}