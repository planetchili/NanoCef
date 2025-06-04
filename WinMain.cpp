#define NOMINMAX
#include <Windows.h>
#include <filesystem>
#include "NanoCefApp.h"
#include "NanoBrowserWindow.h"

using namespace std::literals;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const CefMainArgs mainArgs{ hInstance };
	CefRefPtr<NanoCefApp> pApp = new NanoCefApp{};
	if (const auto code = CefExecuteProcess(mainArgs, pApp, nullptr); code >= 0) {
		return (int)code;
	}

	CefSettings settings;
	settings.multi_threaded_message_loop = true;
	settings.no_sandbox = true;
	CefString(&settings.cache_path).FromString((std::filesystem::current_path() / "cef_cache"s).string());
	CefInitialize(mainArgs, settings, pApp, nullptr);

	CreateBrowserWindow(hInstance);

	MSG msg;
	while (GetMessageA(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	CleanupBrowserWindow(hInstance);
	CefShutdown();

	return (int)msg.wParam;
}