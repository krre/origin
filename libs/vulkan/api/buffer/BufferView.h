#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"

namespace Vulkan {

class Buffer;

class BufferView : public Handle<VkBufferView>, public Devicer {
public:
    BufferView(Device* device, Buffer* buffer);
    ~BufferView();

    void create() override;

private:
    VkBufferViewCreateInfo m_createInfo = {};
};

}
