#pragma once
#include "../../Core/Common.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>

namespace Vulkan {

class VulkanObject {

public:
    VulkanObject();
    std::string getError() const { return error; }

protected:
    std::string error = "Unknown error";
    static std::map<VkResult, std::string> resultDescription;
};

} // Vulkan
