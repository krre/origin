#pragma once
#include "../../Core/Object.h"
#include <vulkan/vulkan.h>
#include <string>

namespace Vulkan {

class VulkanObject : public Object {

public:
    VulkanObject();
    std::string getError() const { return "Vulkan: " + error; }

protected:
    std::string error = "Unknown error";
};

} // Vulkan
