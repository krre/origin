#pragma once
#include "../../Core/Common.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>

#define ASSERT_ERROR

namespace Vulkan {

class Object {

public:
    Object();
    std::string getResultDescription() const;
    VkResult getResult() const { return result; }
    std::string resultToString(VkResult result);

protected:
    void checkError(VkResult result);

    VkResult result = VK_NOT_READY;
};

} // Vulkan