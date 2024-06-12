#include "DebugReportCallback.h"
#include "Instance.h"

namespace Vulkan {

DebugReportCallback::DebugReportCallback(Instance* instance, PFN_vkDebugReportCallbackEXT debugCallback) : m_instance(instance) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    m_createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    m_createInfo.pfnCallback = debugCallback;
}

DebugReportCallback::~DebugReportCallback() {
    PFN_vkDestroyDebugReportCallbackEXT pfnDestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance->handle(), "vkDestroyDebugReportCallbackEXT");
    if (!pfnDestroyDebugReportCallback) {
        throw std::runtime_error("GetInstanceProcAddr: Unable to find vkDestroyDebugReportCallbackEXT function");
    }
    pfnDestroyDebugReportCallback(m_instance->handle(), m_handle, nullptr);
}

void DebugReportCallback::create() {
    PFN_vkCreateDebugReportCallbackEXT pfnCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance->handle(), "vkCreateDebugReportCallbackEXT");
    if (!pfnCreateDebugReportCallback) {
        throw std::runtime_error("GetInstanceProcAddr: Unable to find vkCreateDebugReportCallbackEXT function");
    }

    VULKAN_CHECK_RESULT(pfnCreateDebugReportCallback(m_instance->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create debug report callback");
}

void DebugReportCallback::setFlags(VkDebugReportFlagsEXT flags) {
    m_createInfo.flags = flags;
}

}
