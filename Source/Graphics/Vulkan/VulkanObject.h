#pragma once
#include "../../Core/Object.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>

namespace Vulkan {

class VulkanObject : public Object {

public:
    VulkanObject();
    std::string getResultDescription() const { return resultDescription[result]; }
    VkResult getResult() const { return result; }

protected:
    VkResult result = VK_SUCCESS;
    static std::map<VkResult, std::string> resultDescription;
};

} // Vulkan
