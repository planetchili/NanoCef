#pragma once
#include "include/cef_app.h"
#include "NanoFileSchemeHandlerFactory.h"

class NanoCefApp : public CefApp,
	public CefBrowserProcessHandler,
    public CefRenderProcessHandler,
    public CefV8Handler
{
public:
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
    {
        return this;
    }
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override
    {
        return this;
    }
    void OnContextInitialized() override
    {
        CefRegisterSchemeHandlerFactory("http", "disk", new NanoFileSchemeHandlerFactory{});
    }
    void OnContextCreated(CefRefPtr<CefBrowser> pBrowser, CefRefPtr<CefFrame> pFrame, CefRefPtr<CefV8Context> pV8Context)
    {
        pV8Context->GetGlobal()->SetValue("doChili", CefV8Value::CreateFunction("doChili", this), V8_PROPERTY_ATTRIBUTE_NONE);
    }
    bool Execute(const CefString& name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList& argPtrs,
        CefRefPtr<CefV8Value>& pRet,
        CefString& exception) override
    {
        const auto ret = MessageBoxA(nullptr, argPtrs[0]->GetStringValue().ToString().c_str(),
            "henlo", MB_SYSTEMMODAL | MB_ICONQUESTION | MB_YESNOCANCEL);
        if (ret == IDCANCEL) {
            exception = "cancelled";
        }
        else {
            pRet = CefV8Value::CreateBool(ret == IDYES);
        }
        return true;
    }

	IMPLEMENT_REFCOUNTING(NanoCefApp);
};
