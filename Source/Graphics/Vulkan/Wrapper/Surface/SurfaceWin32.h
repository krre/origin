#pragma once
#include "Surface.h"
#include <windows.h>

namespace Vulkan {

class SurfaceWin32 : public Surface {

public:
    SurfaceWin32(VkPhysicalDevice physicalDevice, HINSTANCE hinstance, HWND hwnd);

private:
    HINSTANCE hinstance;
    HWND hwnd;
    void platformCreateHandle() override;
};

} // Vulkan
