#pragma once
#include "Surface.h"
#include <windows.h>

namespace Origin {

namespace Vulkan {

class Instance;
class PhysicalDevice;

class Win32Surface : public Surface {

public:
    Win32Surface(Instance* instance, PhysicalDevice* physicalDevice, HINSTANCE hinstance, HWND hwnd);

private:
    HINSTANCE hinstance;
    HWND hwnd;
    void platformCreateHandle() override;
};

} // Vulkan

} // Origin
