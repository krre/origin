#pragma once
#include "HardwareBuffer.h"
#include "Graphics/GraphicsTypes.h"

class IndexBuffer : public HardwareBuffer {

public:
    IndexBuffer(uint64_t count, IndexBufferBits bits = IndexBufferBits::UINT32);

private:
    IndexBufferBits bits;

};
