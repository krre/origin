#pragma once
#include "../../Core/Common.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>

namespace Vulkan {

class VulkanObject {

public:
    VulkanObject();
    std::string getResultDescription() const { return resultDescription[result]; }
    VkResult getResult() const { return result; }

protected:
    std::string error = "Unknown error";
    VkResult result = VK_SUCCESS;
    static std::map<VkResult, std::string> resultDescription;

};

} // Vulkan
