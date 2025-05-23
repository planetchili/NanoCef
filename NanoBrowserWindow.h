#pragma once
#define NOMINMAX
#include <Windows.h>

HWND CreateBrowserWindow(HINSTANCE hInstance);
void CleanupBrowserWindow(HINSTANCE hInstance);