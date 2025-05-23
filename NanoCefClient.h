#pragma once
#include "include/cef_client.h"

class NanoCefClient : public CefClient,
	public CefLifeSpanHandler
{
public:
	CefRefPtr<CefBrowser> GetBrowser()
	{
		return pBrowser_;
	}
	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
	{
		return this;
	}
	void OnAfterCreated(CefRefPtr<CefBrowser> pBrowser) override
	{
		pBrowser_ = pBrowser;
	}
private:
	CefRefPtr<CefBrowser> pBrowser_;

	IMPLEMENT_REFCOUNTING(NanoCefClient);
};