#pragma once
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/base/cef_callback.h"
#include "NanoFileSchemeHandlerFactory.h"
#include <future>
#include <unordered_map>

using namespace std::literals;

class NanoCefApp : public CefApp,
	public CefBrowserProcessHandler,
    public CefRenderProcessHandler,
    public CefV8Handler
{
    struct Invocation_
    {
        CefRefPtr<CefV8Value> pAccept;
        CefRefPtr<CefV8Value> pReject;
        CefRefPtr<CefV8Context> pV8Context;
        std::future<void> task;
    };
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
        const auto id = nextInvocationId_++;
        auto& invocation = invocations_[id];
        invocation.pAccept = argPtrs[1];
        invocation.pReject = argPtrs[2];
        invocation.pV8Context = CefV8Context::GetCurrentContext();
        invocation.task = std::async([this, text = argPtrs[0]->GetStringValue().ToString(), id] {
            const auto ret = MessageBoxA(nullptr, text.c_str(),
                "henlo", MB_SYSTEMMODAL | MB_ICONQUESTION | MB_YESNOCANCEL);
            CefPostTask(TID_RENDERER, base::BindOnce(&NanoCefApp::ResolveDoChili_, this,
                id, ret == IDYES, ret == IDCANCEL ? "CAN"s : ""s
            ));
        });
        return true;
    }

private:
    void ResolveDoChili_(uint32_t id, bool yesno, std::string exception)
    {
        auto& invocation = invocations_[id];
        invocation.pV8Context->Enter();
        if (!exception.empty()) {
            invocation.pReject->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateString(exception) });
        }
        else {
            invocation.pAccept->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateBool(yesno) });
        }
        invocation.pV8Context->Exit();
        invocations_.erase(id);
    }

    uint32_t nextInvocationId_ = 0;
    std::unordered_map<uint32_t, Invocation_> invocations_;

	IMPLEMENT_REFCOUNTING(NanoCefApp);
};
