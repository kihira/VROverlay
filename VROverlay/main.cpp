#include <openvr.h>
#include <iostream>

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

    while (true)
    {
        // todo update loop
    }
}