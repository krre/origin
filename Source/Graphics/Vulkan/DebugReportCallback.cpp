#include "DebugReportCallback.h"

using namespace Vulkan;

DebugReportCallback::DebugReportCallback(const Instance* instance) : instance(instance) {
    pfnCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance->getHandle(), "vkCreateDebugReportCallbackEXT");
    if (!pfnCreateDebugReportCallback) {
        error("GetInstanceProcAddr: Unable to find vkCreateDebugReportCallbackEXT function");
    }

    pfnDestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance->getHandle(), "vkDestroyDebugReportCallbackEXT");
    if (!pfnDestroyDebugReportCallback) {
        error("GetInstanceProcAddr: Unable to find vkDestroyDebugReportCallbackEXT function");
    }

    VkDebugReportCallbackCreateInfoEXT createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    result = pfnCreateDebugReportCallback(instance->getHandle(), &createInfo, nullptr, &handle);
}

DebugReportCallback::~DebugReportCallback() {
    if (handle != VK_NULL_HANDLE) {
        pfnDestroyDebugReportCallback(instance->getHandle(), handle, nullptr);
    }
}
