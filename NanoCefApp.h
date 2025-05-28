#pragma once
#include "include/cef_app.h"
#include "NanoFileSchemeHandlerFactory.h"

class NanoCefApp : public CefApp,
	public CefBrowserProcessHandler
{
public:
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
    {
        return this;
    }
    void OnContextInitialized() override
    {
        CefRegisterSchemeHandlerFactory("http", "disk", new NanoFileSchemeHandlerFactory{});
    }

	IMPLEMENT_REFCOUNTING(NanoCefApp);
};
