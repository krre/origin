#pragma once
#include "../../Core/Singleton.h"
#include <string>

const std::string initError = "Vulkan initialization error\n\n";

class VulkanManager : public Singleton<VulkanManager> {

public:
    VulkanManager();
    bool init();
    std::string getError() const { return error; }

private:
    std::string error = "Undefined error";
};
