#include "DebugReportCallback.h"
#include "Instance.h"

namespace Vulkan {

DebugReportCallback::DebugReportCallback(Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback) : instance(instance) {
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;
}

DebugReportCallback::~DebugReportCallback() {
    destroy();
}

void DebugReportCallback::create() {
    PFN_vkCreateDebugReportCallbackEXT pfnCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance->handle(), "vkCreateDebugReportCallbackEXT");
    if (!pfnCreateDebugReportCallback) {
        throw std::runtime_error("GetInstanceProcAddr: Unable to find vkCreateDebugReportCallbackEXT function");
    }

    VULKAN_CHECK_RESULT(pfnCreateDebugReportCallback(instance->handle(), &createInfo, nullptr, &m_handle), "Failed to create debug report callback");
}

void DebugReportCallback::destroy() {
    PFN_vkDestroyDebugReportCallbackEXT pfnDestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance->handle(), "vkDestroyDebugReportCallbackEXT");
    if (!pfnDestroyDebugReportCallback) {
        throw std::runtime_error("GetInstanceProcAddr: Unable to find vkDestroyDebugReportCallbackEXT function");
    }
    pfnDestroyDebugReportCallback(instance->handle(), m_handle, nullptr);
}

void DebugReportCallback::setFlags(VkDebugReportFlagsEXT flags) {
    createInfo.flags = flags;
}

}
