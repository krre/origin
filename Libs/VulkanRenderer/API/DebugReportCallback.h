#pragma once
#include "Base/Handle.h"
#include <iostream>
#include <iomanip>

namespace Origin {

namespace Vulkan {

    class Instance;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallbackDefault(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object,
                                                           size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* userData) {
    std::string log;
    switch (flags) {
    case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
        log = "INFO";
        break;
    case VK_DEBUG_REPORT_WARNING_BIT_EXT:
        log = "WARN";
        break;
    case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
        log = "PERF";
        break;
    case VK_DEBUG_REPORT_ERROR_BIT_EXT:
        log = "ERROR";
        break;
    case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
        log = "DEBUG";
        break;
    }

    std::cout << "[" << log << "] " << pLayerPrefix << " | object: " << std::hex << "0x" << object << std::dec << " | type: " << objectType
              << " | location: " << location << " | code: " << messageCode << std::endl << pMessage << std::endl;

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
