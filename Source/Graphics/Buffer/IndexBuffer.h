#pragma once
#include "HardwareBuffer.h"

class IndexBuffer : public HardwareBuffer {

public:

    enum class Type {
        UINT16,
        UINT32
    };

    IndexBuffer(uint64_t count, Type type = Type::UINT32);

private:
    Type type;

};
