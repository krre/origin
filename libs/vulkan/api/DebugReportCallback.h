#pragma once
#include "base/Handle.h"
#include <iostream>
#include <iomanip>

namespace Vulkan {

    class Instance;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallbackDefault(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object,
                                                           size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* userData) {
    std::string log;
    switch (flags) {
        case VK_DEBUG_REPORT_INFORMATION_BIT_EXT: log = "INFO"; break;
        case VK_DEBUG_REPORT_WARNING_BIT_EXT: log = "WARN"; break;
        case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT: log = "PERF"; break;
        case VK_DEBUG_REPORT_ERROR_BIT_EXT: log = "ERROR"; break;
        case VK_DEBUG_REPORT_DEBUG_BIT_EXT: log = "DEBUG"; break;
    }

    std::string type = "Not found";
    switch (objectType) {
        case VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT: type = "Unknown"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT: type = "Instance";
        case VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT: type = "Physical device";
        case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT: type = "Device"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT: type = "Queue"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT: type = "Semaphore"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT: type = "Command buffer"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT: type = "Fence"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT: type = "Device memory"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT: type = "Buffer"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT: type = "Image"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT: type = "Event"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT: type = "Query pool"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT: type = "Buffer view"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT: type = "Image view"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT: type = "Shader module"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT: type = "Pipeline cache"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT: type = "Pipeline layout"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT: type = "Render pass"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT: type = "Pipeline"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT: type = "Descriptor set layout"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT: type = "Sampler"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT: type = "Descriptor pool"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT: type = "Descriptor set"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT: type = "Framebuffer"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT: type = "Command pool"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT: type = "Surface"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT: type = "Swapchain"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT_EXT: type = "Debug report callback"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT: type = "Display"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT: type = "Display mode"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT: type = "Validation cache"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT: type = "Sampler YCBCR conversion"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT: type = "Descriptor update template"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_CU_MODULE_NVX_EXT: type = "CU module"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_CU_FUNCTION_NVX_EXT: type = "CU function"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR_EXT: type = "Acceleration structure"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV_EXT: type = "Acceleration structure"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_CUDA_MODULE_NV_EXT: type = "CUDE module"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_CUDA_FUNCTION_NV_EXT: type = "CUDE function"; break;
        case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_COLLECTION_FUCHSIA_EXT: type = "Buffer collection Fuchsia"; break;
    }

    std::cout << "[" << log << "] " << pLayerPrefix << " | object: " << std::hex << "0x" << object << std::dec << " | type: " << type
              << " | location: " << location << " | code: " << messageCode << " | message: " << pMessage << std::endl;

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
    Instance* m_instance = nullptr;
    VkDebugReportCallbackCreateInfoEXT m_createInfo = {};
};

}
