#pragma once
#include "Base/Handle.h"
#include <iostream>

namespace Origin {

namespace Vulkan {

    class Instance;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallbackDefault(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object,
                                                           size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* userData) {
    std::cerr << "Validation layer: " << pMessage << std::endl;

    return VK_FALSE;
}

class DebugReportCallback : public Handle<VkDebugReportCallbackEXT> {

public:
    DebugReportCallback(Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback = debugCallbackDefault);
    ~DebugReportCallback();

    void create() override;
    void destroy() override;

    void setFlags(VkDebugReportFlagsEXT flags);

private:
    Instance* instance;
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
};

} // Vulkan

} // Origin
