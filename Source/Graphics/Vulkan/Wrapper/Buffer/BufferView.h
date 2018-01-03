#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

namespace Origin {

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

} // Origin
