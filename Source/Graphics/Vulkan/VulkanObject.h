#pragma once
#include "../../Core/Common.h"
#include <vulkan/vulkan.h>
#include <string>

namespace Vulkan {

class VulkanObject {

public:
    VulkanObject();
    std::string getError() const { return "Vulkan: " + error; }

protected:
    std::string error = "Unknown error";
};

} // Vulkan
