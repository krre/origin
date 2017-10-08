#pragma once
#include "Surface.h"
#include <windows.h>

namespace Vulkan {

class Win32Surface : public Surface {

public:
    Win32Surface(VkPhysicalDevice physicalDevice, HINSTANCE hinstance, HWND hwnd);

private:
    HINSTANCE hinstance;
    HWND hwnd;
    void platformCreateHandle() override;
};

} // Vulkan
