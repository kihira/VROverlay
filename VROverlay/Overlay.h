#pragma once
#include <openvr.h>
#include <d3d11.h>
#include <string>

class Overlay
{
public:
    Overlay(std::string name);
    ~Overlay();
    void SetTexture(ID3D11Texture2D* ptr);
    void SetColor(float red, float green, float blue);
    void SetAlpha(float alpha);
    void SetWidth(float width);
    void SetVisible(bool visible);
    void SetTextureBounds(float uMin, float uMax, float vMin, float vMax);
private:
    std::string key;
    std::string name;
    vr::VROverlayHandle_t* handle = nullptr;
    float color[3] = {1.f, 1.f, 1.f};
    float alpha = 1.f;
    float width = 1.f;
    bool visible = true;
    vr::VRTextureBounds_t texture_bounds = { 0.f, 1.f, 0.f, 1.f };
};

