#include "Surface.h"
#include "../../Core/App.h"
#include <SDL_syswm.h>

using namespace Vulkan;

Surface::Surface(const Instance* instance) : instance(instance) {
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(App::get()->getWindow(), &wminfo);
    print(wminfo.subsystem)
}
