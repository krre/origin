#pragma once
#include "Surface.h"
#include <windows.h>

#undef TRANSPARENT // Fix conflict with Color::TRANSPARENT const

namespace Vulkan {

class Win32Surface : public Surface {

public:
    Win32Surface(Instance* instance, PhysicalDevice* physicalDevice, HINSTANCE hinstance, HWND hwnd);

private:
    HINSTANCE hinstance;
    HWND hwnd;
    void platformCreateHandle() override;
};

} // Vulkan
