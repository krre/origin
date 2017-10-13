#pragma once
#include "Surface.h"
#include <windows.h>

namespace Vulkan {

class Instance;

class Win32Surface : public Surface {

public:
    Win32Surface(Instance* instance, VkPhysicalDevice physicalDevice, HINSTANCE hinstance, HWND hwnd);

private:
    HINSTANCE hinstance;
    HWND hwnd;
    void platformCreateHandle() override;
};

} // Vulkan
