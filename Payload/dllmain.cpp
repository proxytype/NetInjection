// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MSCorEE.h"
#include "MetaHost.h"

#pragma comment(lib, "mscoree.lib")

void netRuntime() {

    ICLRMetaHost* pClrHost = NULL;
    HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pClrHost);

    ICLRRuntimeInfo* pRuntimeInfo = NULL;
    pClrHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (LPVOID*)&pRuntimeInfo);

    ICLRRuntimeHost* pClrRuntimeHost = NULL;
    pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&pClrRuntimeHost);

    hr = pClrRuntimeHost->Start();

    hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(L"C:\\Users\\Starscream\\Desktop\\NetInjection\\NetInjection\\bin\\Debug\\NetInjection.dll", L"NetInjection.NetPayload", L"showInjection", NULL, NULL);
    hr = pClrRuntimeHost->Stop();

    pClrRuntimeHost->Release();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        netRuntime();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

