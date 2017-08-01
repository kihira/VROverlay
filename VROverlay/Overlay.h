#pragma once
#include <openvr.h>
#include <d3d11.h>

class Overlay
{
public:
    Overlay(const char* name);
    ~Overlay();
    void SetTexture(ID3D11Texture2D* ptr);
    void SetColor(float red, float green, float blue);
    void SetAlpha(float alpha);
    void SetWidth(float width);
    void SetTextureBounds(float uMin, float uMax, float vMin, float vMax);
private:
    const char* key;
    const char* name;
    vr::VROverlayHandle_t* handle = nullptr;
    float color[3] = {1.f, 1.f, 1.f};
    float alpha = 1.f;
    float width = 1.f;
    vr::VRTextureBounds_t texture_bounds = { 0.f, 1.f, 0.f, 1.f };
};

