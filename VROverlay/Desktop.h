#pragma once
#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl/client.h>

enum State
{
    NotStarted,
    Valid,
    Error
};

class Desktop
{
public:
    Desktop(int num);
    ~Desktop();
    void Initialise(Microsoft::WRL::ComPtr<IDXGIAdapter1>& adapter, Microsoft::WRL::ComPtr<IDXGIOutput>& output);
    ID3D11Texture2D* GetDesktop();
    void ReleaseFrame();
    bool Valid() const;
private:
    IDXGIOutputDuplication* desktop;
    ID3D11Texture2D* desktopImage;
    State state;
};