#include "Surface.h"
#include "../../Core/App.h"
#include <SDL_syswm.h>
#ifdef __linux__
    #include <X11/Xlib-xcb.h>
#elif _WIN32

#endif


using namespace Vulkan;

Surface::Surface(const Instance* instance) : instance(instance) {
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(App::get()->getWindow(), &wminfo);

    switch (wminfo.subsystem) {
#ifdef __linux__
    case SDL_SYSWM_X11: {
        VkXcbSurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.flags = 0;
        createInfo.connection = XGetXCBConnection(wminfo.info.x11.display);
        createInfo.window = wminfo.info.x11.window;
        result = vkCreateXcbSurfaceKHR(instance->getHandle(), &createInfo, nullptr, &handle);
        break;
    }

#elif _WIN32
    case SDL_SYSWM_WINDOWS: {
        VkWin32SurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.flags = 0;
        createInfo.hwnd = wminfo.info.win.window;
        createInfo.hinstance = GetModuleHandle(nullptr);
        result = vkCreateWin32SurfaceKHR(instance->getHandle(), &createInfo, nullptr, &handle);
        break;
    }
#endif

    }
}

Surface::~Surface() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance->getHandle(), handle, nullptr);
    }
}
