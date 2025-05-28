#pragma once
#include "include/cef_scheme.h"
#include "NanoFileResourceHandler.h"

class NanoFileSchemeHandlerFactory : public CefSchemeHandlerFactory
{
public:
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        const CefString& scheme_name,
        CefRefPtr<CefRequest> request) override
    {
        return new NanoFileResourceHandler{};
    }

    IMPLEMENT_REFCOUNTING(NanoFileSchemeHandlerFactory);
};