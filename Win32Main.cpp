﻿#include "XPlatform.h"
#include "InitializeScene.h"
//#include "Win32Application.h"
#include <windows.h> // GetConsoleWindow(), ShowWindow(), ExitProcess().


/////////////////////////////////////////////////////////////////////////////
// @ 진입점.
/////////////////////////////////////////////////////////////////////////////
//int32_t __stdcall wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int32_t)
int32_t main()
{
	// 콘솔 감추기.
	auto consoleWindowHandle = GetConsoleWindow(); // consoleapi3.h
	ShowWindow(consoleWindowHandle, SW_HIDE); // WinUser.h

	// 어플리케이션 실행.
	XPlatform::StartApplication(std::make_shared<InitializeScene>(), 1280, 640, false);
	ExitProcess(0); // processthreadsapi.h
	return 0;
}
