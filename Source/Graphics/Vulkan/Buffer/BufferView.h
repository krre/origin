#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"

namespace Vulkan {

class Buffer;

class BufferView : public Handle<VkBufferView>, public Devicer {

public:
    BufferView(Device* device, Buffer* buffer);
    ~BufferView();
    void create() override;
    void destroy() override;

private:
    VkBufferViewCreateInfo createInfo = {};
};

} // Vulkan
