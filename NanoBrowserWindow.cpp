#include "NanoBrowserWindow.h"
#include "NanoCefClient.h"

using namespace std::literals;

static constexpr const char* wndClassName = "$browser-window$";
static CefRefPtr<NanoCefClient> pClient;

LRESULT CALLBACK BrowserWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE: {
		pClient = new NanoCefClient{};

		RECT rect{};
		GetClientRect(hWnd, &rect);
		CefRect cefRect;
		cefRect.x = rect.left;
		cefRect.y = rect.top;
		cefRect.width = rect.right - rect.left;
		cefRect.height = rect.bottom - rect.top;

		CefWindowInfo info;
		info.SetAsChild(hWnd, cefRect);

		CefBrowserHost::CreateBrowser(info, pClient, "https://youtube.com"s, {}, {}, {});
		break;
	}
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED && pClient) {
			if (auto pBrowser = pClient->GetBrowser()) {
				if (auto hWndBrowser = pBrowser->GetHost()->GetWindowHandle()) {
					RECT rect{};
					GetClientRect(hWnd, &rect);
					SetWindowPos(hWndBrowser, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
				}
			}
		}
		break;
	case WM_ERASEBKGND:
		if (pClient) {
			if (auto pBrowser = pClient->GetBrowser()) {
				if (pBrowser->GetHost()->GetWindowHandle()) {
					return 1;
				}
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


HWND CreateBrowserWindow(HINSTANCE hInstance)
{
	HWND hWndBrowser = nullptr;
	WNDCLASSEXA wcex{};
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BrowserWindowWndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszClassName = wndClassName;
	RegisterClassExA(&wcex);

	hWndBrowser = CreateWindowExA(
		0, wndClassName, "Nano CEF",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 200, 20,
		1360, 1020, nullptr, nullptr, hInstance, nullptr
	);

	ShowWindow(hWndBrowser, SW_SHOWDEFAULT);
	UpdateWindow(hWndBrowser);

	return hWndBrowser;
}

void CleanupBrowserWindow(HINSTANCE hInstance)
{
	pClient.reset();
	UnregisterClassA(wndClassName, hInstance);
}
