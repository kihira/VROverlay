#include <openvr.h>
#include <iostream>
#include <d3d11.h>
#include <memory>
#include <wrl/client.h>
#include "Desktop.h"

int main(int argc, char* argv[])
{
    vr::HmdError err = vr::VRInitError_None;;
    vr::IVRSystem* system = VR_Init(&err, vr::VRApplication_Overlay);

    if (err != vr::VRInitError_None)
    {
        vr::VR_Shutdown();
        std::cerr << "Failed to initialise VR interface: " << VR_GetVRInitErrorAsSymbol(err) << std::endl;
        return -1;
    }

    UINT flags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    ID3D11Device* device;
    D3D_FEATURE_LEVEL featureLevel;
    ID3D11DeviceContext* context;
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0, D3D11_SDK_VERSION, &device, &featureLevel, &context)))
    {
        MessageBox(nullptr, L"Failed to create D3D11 device", nullptr, 0);
        return -1;
    }
    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        MessageBox(nullptr, L"Direct3D Feature Level 11 unsupported.", nullptr, 0);
        return false;
    }

    while (true)
    {
        // todo update loop
    }
}

void LoadMonitors()
{
    Microsoft::WRL::ComPtr<IDXGIFactory1> factory;
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        std::cerr << "Failed to create DXGI factory" << std::endl;
        return;
    }

    int id = 0;
    // Loop through display adapters (GPU)
    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
    for (int i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++)
    {
        // Loop through monitors
        Microsoft::WRL::ComPtr<IDXGIOutput> output;
        for (int j = 0; adapter->EnumOutputs(j, &output) != DXGI_ERROR_NOT_FOUND; j++)
        {
            auto monitor = std::make_shared<Desktop>(id++);
            monitor->Initialise(adapter, output);
        }
    }
}