#pragma once
#include "../../Core/Object.h"
#include <vulkan/vulkan.h>
#include <string>

namespace Vulkan {

class Instance : public Object {

public:
    Instance();
    ~Instance();
    bool create();
    VkInstance* getInstance() const { return pInstance; }

private:
    VkInstance* pInstance = nullptr;
    VkInstanceCreateInfo* pCreateInfo = nullptr;
    std::string error = "Unknown error";

};

} // Vulkan
