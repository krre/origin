#pragma once
#include "VkObject.h"
#include "Instance.h"

namespace Vulkan {

class DebugReportCallback : public VkObject {

public:
    DebugReportCallback(const Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback);
    ~DebugReportCallback();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkDebugReportCallbackEXT getHandle() const { return handle; }

private:
    VkDebugReportCallbackEXT handle = VK_NULL_HANDLE;
    const Instance* instance;

    PFN_vkCreateDebugReportCallbackEXT pfnCreateDebugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT pfnDestroyDebugReportCallback;
};

} // Vulkan
