#include "Desktop.h"
#include <iostream>

Desktop::Desktop(int num) : state(NotStarted)
{
}

Desktop::~Desktop()
{
}

void Desktop::Initialise(Microsoft::WRL::ComPtr<IDXGIAdapter1>& adapter, Microsoft::WRL::ComPtr<IDXGIOutput>& output)
{
    HRESULT hr = S_OK;
    IDXGIOutput1* output1 = nullptr;

    hr = output->QueryInterface(__uuidof(IDXGIOutput1), reinterpret_cast<void**>(&output1));
    if (FAILED(hr))
    {
        state = Error;
        std::cerr << "Desktop::Initialise() -> Failed to get IDXGIOutput1" << std::endl;
        return;
    }

    hr = output1->DuplicateOutput(adapter.Get(), &desktop);
    if (FAILED(hr))
    {
        state = Error;
        std::cerr << "Desktop::Initialise() -> Failed to begin desktop duplication:" << std::endl;
        switch (hr)
        {
            case E_INVALIDARG:
                std::cerr << "Device is invalid or already duplicating" << std::endl;
                break;
            case E_ACCESSDENIED:
                std::cerr << "Access denied, possibly trying to capture secure screen?" << std::endl;
                break;
            case DXGI_ERROR_UNSUPPORTED:
                std::cerr << "Desktop is not supported" << std::endl;
                break;
            case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
                std::cerr << "Too many applications duplicating! (Limit of 4)" << std::endl;
                break;
            default:
                std::cerr << "Unhandled error (" << hr << ")" << std::endl;
                break;
        }
        return;
    }

    state = State::Valid;
}

ID3D11Texture2D* Desktop::GetDesktop()
{
    HRESULT hr = S_OK;
    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    IDXGIResource* resource = nullptr;

    hr = desktop->AcquireNextFrame(20, &frameInfo, &resource);
    if (FAILED(hr))
    {
        state = Error;
        std::cerr << "Desktop::GetDesktop() -> Failed to aquire next frame:" << std::endl;
        switch (hr)
        {
        case DXGI_ERROR_ACCESS_LOST:
            std::cerr << "Interface access lost. Another application may have taken control" << std::endl;
            break;
        case DXGI_ERROR_WAIT_TIMEOUT:
            std::cerr << "Time out whilst trying to get next frame" << std::endl;
            break;
        default:
            std::cerr << "Unhandled error (" << hr << ")" << std::endl;
            break;
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
        state = Error;
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

bool Desktop::Valid() const
{
    return state == State::Valid;
}
