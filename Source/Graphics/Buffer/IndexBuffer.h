#pragma once
#include "HardwareBuffer.h"

class IndexBuffer : public HardwareBuffer {

public:
    IndexBuffer(uint64_t count);
    VkIndexType getIndexType() const { return indexType; }

private:
    VkIndexType indexType = VK_INDEX_TYPE_UINT32;
};
