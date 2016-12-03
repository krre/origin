#pragma once
#include "../../Core/Common.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>

namespace Vulkan {

class Object {

public:
    Object();
    std::string getResultDescription() const;
    VkResult getResult() const { return result; }
    std::string resultToString(VkResult result) const;

protected:
    bool checkError(VkResult result, const char* message);

    VkResult result;
};

} // Vulkan
