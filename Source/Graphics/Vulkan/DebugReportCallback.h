#pragma once
#include "VkCreatableObject.h"
#include "Instance.h"

namespace Vulkan {

class DebugReportCallback : public VkCreatableObject<VkDebugReportCallbackEXT> {

public:
    DebugReportCallback(const Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback);
    ~DebugReportCallback();
    void create() override;

private:
    const Instance* instance;
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    PFN_vkCreateDebugReportCallbackEXT pfnCreateDebugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT pfnDestroyDebugReportCallback;
};

} // Vulkan
