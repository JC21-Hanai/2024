/// <summary>
/// CoGフレームワーク
/// WinMain()から始まります
/// </summary>
/// <author>N.Hanai</author>
/// 
#define _CRTDBG_MAP_ALLOC
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__);
#else
#define DBG_NEW new
#endif
#endif

#define IMGUI 1
#include <DxLib.h>
#include "App.h"
#include "../Source/Screen.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

#define CoGVersion "4.5F"

const char* Version() {
	return CoGVersion;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ログを出さない

	SetMainWindowText(Screen::WINDOW_NAME);
	SetWindowSizeExtendRate(Screen::WINDOW_EXTEND);
	ChangeWindowMode(Screen::WINDOW_MODE); // Windowモードの場合

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
	{
		// DxLibとImGuiのウィンドウプロシージャを両立させる
		SetUseHookWinProcReturnValue(FALSE);
		return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	});
#if IMGUI
	// ImGUI初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.Fonts->AddFontFromFileTTF(u8"c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());	ImGui_ImplDXlib_Init();
#endif
	AppInit();
#ifdef FIX_FRAME_RATE
	float refreshTime;
	float freq;
	LONGLONG lastTime;
	if (Screen::FRAME_RATE <= 0.0f) {
		HDC hdc = GetDC(GetMainWindowHandle());	// デバイスコンテキストの取得
		float refreshRate = (float)GetDeviceCaps(hdc, VREFRESH);	// リフレッシュレートの取得
		refreshTime = 1.0f / refreshRate;
		ReleaseDC(GetMainWindowHandle(), hdc);	// デバイスコンテキストの解放
	} else {
		int d = Screen::FRAME_RATE;
		refreshTime = 1.0f / d;
	}
	{
		LARGE_INTEGER freqL;
		QueryPerformanceFrequency(&freqL);
		freq = freqL.QuadPart;
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		lastTime = current.QuadPart;
	}
#endif
	while (true) {
#ifdef FIX_FRAME_RATE
		while(true) {
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			float dt = static_cast<float>(current.QuadPart - lastTime) / freq;
			if (dt >= refreshTime) {
				lastTime = current.QuadPart;
				break;
			}
		}
#endif
#if IMGUI
		ImGui_ImplDXlib_NewFrame();
		ImGui::NewFrame();
#endif

		AppUpdate();

		if (ProcessMessage() == -1 || AppIsExit())
		{
			break;
		}
		ScreenFlip();
		ClearDrawScreen();
		AppDraw();
#if IMGUI
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDXlib_RenderDrawData();
#endif
		RefreshDxLibDirect3DSetting();
#if IMGUI
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
#endif
	}
	AppRelease();
#if IMGUI
	ImGui_ImplDXlib_Shutdown();
	ImGui::DestroyContext();
#endif
	DxLib_End();				// ＤＸライブラリ使用の終了処理
#ifdef _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
#endif
#endif
	return 0;				// ソフトの終了 
}