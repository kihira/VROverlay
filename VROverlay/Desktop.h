#pragma once
#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl/client.h>

class Desktop
{
public:
    Desktop(int num);
    ~Desktop();
    void Initialise(Microsoft::WRL::ComPtr<IDXGIAdapter1>& adapter, Microsoft::WRL::ComPtr<IDXGIOutput>& output);
    ID3D11Texture2D* GetDesktop();
    void ReleaseFrame();
private:
    IDXGIOutputDuplication* desktop;
    ID3D11Texture2D* desktopImage;
};

