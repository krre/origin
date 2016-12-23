#pragma once
#include "../../../Core/Common.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>
#include <assert.h>

#define CHECK_RESULT(result, message) { \
    \
    if ((result) != VK_SUCCESS) { \
        error(std::string((message)) + ": \"" + resultToString((result)) << "\" in " << __FILE__ << " at line " << __LINE__); \
        assert((result) == VK_SUCCESS); \
    } \
}

namespace Vulkan {

class Resulter {

public:
    Resulter() = default;
    std::string getResultDescription() const;
    VkResult getResult() const { return result; }
    std::string resultToString(VkResult result) const;

protected:
    VkResult checkError(VkResult result, const char* message);

    VkResult result;
};

} // Vulkan
