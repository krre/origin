#include "Surface.h"
#include "../../Core/App.h"
#include <SDL_syswm.h>
#include <X11/Xlib-xcb.h>

using namespace Vulkan;

Surface::Surface(const Instance* instance) : instance(instance) {
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(App::get()->getWindow(), &wminfo);

    switch (wminfo.subsystem) {
        case SDL_SYSWM_X11: {
            VkXcbSurfaceCreateInfoKHR createInfo;
            createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
            createInfo.flags = 0;
            createInfo.connection = XGetXCBConnection(wminfo.info.x11.display);
            createInfo.window = wminfo.info.x11.window;

            result = vkCreateXcbSurfaceKHR(instance->getHandle(), &createInfo, nullptr, &handle);
            print("X11: " << result)
            break;
        }
        case SDL_SYSWM_WINDOWS: {
            print("Windows")
            break;
        }
    }
}
