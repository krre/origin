#pragma once
#include "Base/Handle.h"

namespace Vulkan {
    class Instance;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallbackDefault(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
//    std::cerr << "Validation layer: " << msg << std::endl;

    return VK_FALSE;
}

class DebugReportCallback : public Handle<VkDebugReportCallbackEXT> {

public:
    DebugReportCallback(Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback = debugCallbackDefault);
    ~DebugReportCallback();
    void create() override;
    void destroy() override;

private:
    Instance* instance;
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
};

} // Vulkan
