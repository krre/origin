#pragma once
#include "Base/Handle.h"
#include "Instance.h"

namespace Vulkan {

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallbackDefault(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
//    std::cerr << "Validation layer: " << msg << std::endl;

    return VK_FALSE;
}

class DebugReportCallback : public Handle<VkDebugReportCallbackEXT> {

public:
    DebugReportCallback(const Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback = debugCallbackDefault);
    ~DebugReportCallback();
    VkResult create() override;
    void destroy() override;

    VkDebugReportCallbackCreateInfoEXT createInfo = {};

private:
    const Instance* instance;
    PFN_vkCreateDebugReportCallbackEXT pfnCreateDebugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT pfnDestroyDebugReportCallback;
};

} // Vulkan
