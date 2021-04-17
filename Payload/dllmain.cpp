// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MSCorEE.h"
#include "MetaHost.h"

#pragma comment(lib, "mscoree.lib")

ICLRMetaHost* pClrMetaHost = NULL;
ICLRRuntimeInfo* pClrRuntimeInfo = NULL;
ICLRRuntimeHost* pClrRuntimeHost = NULL;

void clrCleanup() {
    if (pClrRuntimeHost)
    {
        pClrRuntimeHost->Release();
        pClrRuntimeHost = NULL;
    }
    if (pClrRuntimeInfo)
    {
        pClrRuntimeInfo->Release();
        pClrRuntimeInfo = NULL;
    }
    if (pClrMetaHost)
    {
        pClrMetaHost->Release();
        pClrMetaHost = NULL;
    }
}


BOOL StartCLR(LPCWSTR dotNetVersion)
{
    HRESULT hr;

    hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pClrMetaHost);
    if (hr == S_OK)
    {
        OutputDebugString(L"CLR INSTANCE");
        // Get the runtime information for the particular version of .NET
        hr = pClrMetaHost->GetRuntime(dotNetVersion, IID_PPV_ARGS(&pClrRuntimeInfo));
        if (hr == S_OK)
        {
            OutputDebugString(L"CLR RUNTIME");

            BOOL fLoadable;
            hr = pClrRuntimeInfo->IsLoadable(&fLoadable);
            if ((hr == S_OK) && fLoadable)
            {
                OutputDebugString(L"CLR LOADED");

                hr = pClrRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,
                    IID_PPV_ARGS(&pClrRuntimeHost));
                if (hr == S_OK)
                {
                    OutputDebugString(L"CLR INTERFACE");
                    hr = pClrRuntimeHost->Start();
                    OutputDebugString(L"CLR START");
                    return TRUE;
                }
            }
        }
    }
    
  
    clrCleanup();
    return FALSE;
}


void netRuntime() {

    OutputDebugString(L"Runtime");
    HRESULT hr;
    BOOL f = StartCLR(L"v4.0.30319");

    if (f == TRUE) {
        DWORD returnVAL;
        hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(L"C:\\Users\\Starscream\\Desktop\\NetInjection\\NetInjection\\bin\\x64\\Debug\\NetInjection.dll", L"NetInjection.NetPayload", L"showInjection", L"UnManaged", &returnVAL);
    }
    else {
        OutputDebugString(L"CLR LOAD FAILURE");
    }
    
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugString(L"Attached!");
        netRuntime();
        break;
    }
    return TRUE;
}

