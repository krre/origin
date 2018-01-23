#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"

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
