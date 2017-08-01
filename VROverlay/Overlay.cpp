#include "Overlay.h"
#include <iostream>

Overlay::Overlay(const char* name) : name(name)
{
    key = rand();
    vr::VROverlayError err = vr::VROverlay()->CreateOverlay(key, name, handle);
    if (err != vr::VROverlayError_None)
    {
        std::cerr << "Failed to create Overlay (" << name << "): " << vr::VROverlay()->GetOverlayErrorNameFromEnum(err) << std::endl;
    }
}

Overlay::~Overlay()
{
    if (handle != nullptr) vr::VROverlay()->DestroyOverlay(*handle);

    delete handle;
}

void Overlay::SetTexture(ID3D11Texture2D* ptr)
{
    vr::Texture_t texture = {ptr, vr::TextureType_DirectX, vr::ColorSpace_Gamma };

    vr::EVROverlayError err = vr::VROverlay()->SetOverlayTexture(*handle, &texture);
    if (err != vr::VROverlayError_None)
    {
        std::cerr << "Failed to set overlay texture (" << name << "): " << vr::VROverlay()->GetOverlayErrorNameFromEnum(err) << std::endl;
    }
}

void Overlay::SetColor(float red, float green, float blue)
{
    this->color[0] = red;
    this->color[1] = green;
    this->color[2] = blue;

    vr::EVROverlayError err = vr::VROverlay()->SetOverlayColor(*handle, red, green, blue);
    if (err != vr::VROverlayError_None)
    {
        std::cerr << "Failed to set overlay color (" << name << "): " << vr::VROverlay()->GetOverlayErrorNameFromEnum(err) << std::endl;
    }
}

void Overlay::SetAlpha(float alpha)
{
    this->alpha = alpha;

    vr::EVROverlayError err = vr::VROverlay()->SetOverlayAlpha(*handle, alpha);
    if (err != vr::VROverlayError_None)
    {
        std::cerr << "Failed to set overlay alpha (" << name << "): " << vr::VROverlay()->GetOverlayErrorNameFromEnum(err) << std::endl;
    }
}

void Overlay::SetWidth(float width)
{
    this->width = width;

    vr::EVROverlayError err = vr::VROverlay()->SetOverlayWidthInMeters(*handle, width);
    if (err != vr::VROverlayError_None)
    {
        std::cerr << "Failed to set overlay width (" << name << "): " << vr::VROverlay()->GetOverlayErrorNameFromEnum(err) << std::endl;
    }
}

void Overlay::SetTextureBounds(float uMin, float uMax, float vMin, float vMax)
{
    this->texture_bounds.uMin = uMin;
    this->texture_bounds.uMax = uMax;
    this->texture_bounds.vMin = vMin;
    this->texture_bounds.vMax = vMax;
}
