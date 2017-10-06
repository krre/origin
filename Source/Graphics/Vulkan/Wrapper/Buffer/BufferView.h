#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class BufferView : public Handle<VkBufferView>, public Devicer {

public:
    BufferView(VkBuffer buffer, Device* device = nullptr);
    ~BufferView();
    void create() override;
    void destroy() override;

private:
    VkBufferViewCreateInfo createInfo = {};
};

} // Vulkan
