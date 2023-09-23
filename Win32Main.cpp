#include "XPlatform.h"
#include "Win32Application.h"
#include "ApplicationListener.h"


/////////////////////////////////////////////////////////////////////////////
// @ ������.
/////////////////////////////////////////////////////////////////////////////
//int32_t __stdcall wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int32_t)
int32_t main()
{
	// �ܼ� ���߱�.
	auto consoleWindowHandle = GetConsoleWindow(); // consoleapi3.h
	ShowWindow(consoleWindowHandle, SW_HIDE); // WinUser.h

	// ���ø����̼� ����.
	XPlatform::StartApplication(std::make_shared<XPlatform::ApplicationListener>(), 1280, 640, false);
	ExitProcess(0); // processthreadsapi.h
	return 0;
}