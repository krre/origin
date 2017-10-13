#pragma once
#include "Surface.h"
#include <X11/Xlib-xcb.h>

namespace Vulkan {

class Instance;

class XcbSurface : public Surface {

public:
    XcbSurface(Instance* instance, VkPhysicalDevice physicalDevice, xcb_connection_t* connection, xcb_window_t window);

private:
    xcb_connection_t* connection;
    xcb_window_t window;
    void platformCreateHandle() override;
};

} // Vulkan
