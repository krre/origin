#include "DebugReportCallback.h"

using namespace Vulkan;

DebugReportCallback::DebugReportCallback(const Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback) : instance(instance) {
    pfnCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance->getHandle(), "vkCreateDebugReportCallbackEXT");
    if (!pfnCreateDebugReportCallback) {
        error("GetInstanceProcAddr: Unable to find vkCreateDebugReportCallbackEXT function");
    }

    pfnDestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance->getHandle(), "vkDestroyDebugReportCallbackEXT");
    if (!pfnDestroyDebugReportCallback) {
        error("GetInstanceProcAddr: Unable to find vkDestroyDebugReportCallbackEXT function");
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;

}

DebugReportCallback::~DebugReportCallback() {
    pfnDestroyDebugReportCallback(instance->getHandle(), handle, nullptr);
}

bool DebugReportCallback::create() {
    return checkError(pfnCreateDebugReportCallback(instance->getHandle(), &createInfo, nullptr, &handle), "Failed to create debug report callback");
}
