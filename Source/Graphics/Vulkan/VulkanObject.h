#pragma once
#include "../../Core/Object.h"
#include <vulkan/vulkan.h>
#include <string>

namespace Vulkan {

class VulkanObject : public Object {

public:
    VulkanObject();

private:
    std::string error = "Unknown error";
};

} // Vulkan
