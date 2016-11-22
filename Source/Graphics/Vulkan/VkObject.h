#pragma once
#include "../../Core/Object.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>

namespace Vulkan {

class VkObject : public Object {

public:
    VkObject();
    std::string getResultDescription() const;
    VkResult getResult() const { return result; }

protected:
    VkResult result = VK_SUCCESS;
};

} // Vulkan
