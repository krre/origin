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
    std::string resultToString(VkResult result);

protected:
    void checkError(VkResult result);

    VkResult result = VK_NOT_READY;
};

} // Vulkan
