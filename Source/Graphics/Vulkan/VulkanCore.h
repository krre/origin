#pragma once
#include "Core/Singleton.h"

namespace Vulkan {
    class Instance;
}

class VulkanCore : public Singleton<VulkanCore> {

public:
    VulkanCore();
    ~VulkanCore();
    Vulkan::Instance* getInstance() const { return instance.get(); }

private:
    std::unique_ptr<Vulkan::Instance> instance;
};
