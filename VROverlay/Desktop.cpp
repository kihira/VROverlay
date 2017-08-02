#include "Desktop.h"
#include <iostream>

Desktop::Desktop(int num)
{
}

Desktop::~Desktop()
{
}

void Desktop::Initialise(Microsoft::WRL::ComPtr<IDXGIAdapter1>& adapter, Microsoft::WRL::ComPtr<IDXGIOutput>& output)
{
    IDXGIOutput1* output1 = nullptr;
    if (FAILED(output->QueryInterface(__uuidof(IDXGIOutput1), reinterpret_cast<void**>(&output1))))
    {
        std::cerr << "Failed to get IDXGIOutput1" << std::endl;
        return;
    }
    output1->DuplicateOutput(adapter.Get(), &desktop);
}

ID3D11Texture2D* Desktop::GetDesktop()
{
    HRESULT hr = S_OK;
    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    IDXGIResource* resource = nullptr;

    hr = desktop->AcquireNextFrame(20, &frameInfo, &resource);
    if (FAILED(hr))
    {
        if (hr == DXGI_ERROR_WAIT_TIMEOUT)
        {
            std::cerr << "Time out whilst trying to get next frame (" << hr << ")" << std::endl;
        }
        else if (hr != DXGI_ERROR_ACCESS_LOST)
        {
            std::cerr << "Failed to acquire next frame in DUPLICATIONMANAGER (" << hr << ")" << std::endl;
        }
        return nullptr;
    }

    if (desktopImage != nullptr)
    {
        desktopImage->Release();
        desktopImage = nullptr;
    }

    hr = resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&desktopImage));
    resource->Release();
    resource = nullptr;
    if (FAILED(hr))
    {
        std::cerr << "Failed to get ID3D11Texture2D from IDXGIResource (" << hr << ")" << std::endl;
        return nullptr;
    }

    return desktopImage;
}

void Desktop::ReleaseFrame()
{
    desktop->ReleaseFrame();

    if (desktopImage != nullptr)
    {
        desktopImage->Release();
        desktopImage = nullptr;
    }
}
