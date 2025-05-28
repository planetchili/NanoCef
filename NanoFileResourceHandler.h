#pragma once
#include "include/cef_resource_handler.h"
#include "include/cef_parser.h"
#include <fstream>
#include <string>
#include <filesystem>


class NanoFileResourceHandler : public CefResourceHandler
{
public:
    bool Open(
        CefRefPtr<CefRequest> pRequest,
        bool& handleRequest,
        CefRefPtr<CefCallback> pCallback) override
    {
        handleRequest = true;
        CefURLParts urlParts;
        CefParseURL(pRequest->GetURL(), urlParts);
        const auto path = std::filesystem::path{ CefString(&urlParts.path).ToString() }.relative_path();
        // file size is needed later to populate the response header when requested
        fileSize_ = (int64_t)std::filesystem::file_size(path);
        // extension is needed later for mime type in the response headers
        auto ext = path.extension().string();
        ext.erase(std::remove(ext.begin(), ext.end(), '.'), ext.end());
        if (!ext.empty()) {
            fileMimeType_ = CefGetMimeType(ext);
        }
        // open the file, success if file is trueish
        fileStream_ = std::ifstream{ path, std::ios::binary };
        return bool(fileStream_);
    }
    void GetResponseHeaders(
        CefRefPtr<CefResponse> pResponse,
        int64_t& responseLength,
        CefString& redirectUrl) override
    {
        if (!fileMimeType_.empty()) {
            pResponse->SetMimeType(fileMimeType_);
        }
        pResponse->SetStatus(200);
        responseLength = fileSize_;
    }
    void Cancel() override {}
    bool Read(
        void* pDataOut,
        int bytesToRead,
        int& bytesRead,
        CefRefPtr<CefResourceReadCallback> pCallback) override
    {
        // if we don't have an out buffer, that's a problem
        if (!pDataOut) {
            bytesRead = -2;
            return false;
        }

        // attempt to read up to bytesToRead
        fileStream_.read(static_cast<char*>(pDataOut), bytesToRead);

        // gcount() is how many bytes we actually got during the last read
        bytesRead = int(fileStream_.gcount());

        // if we got *any* bytes, return true
        // (returning false with bytesRead==0 signals EOF to CEF)
        return bytesRead > 0;
    }
private:
    std::ifstream fileStream_;
    int64_t fileSize_ = 0;
    std::string fileMimeType_;

    IMPLEMENT_REFCOUNTING(NanoFileResourceHandler);
};