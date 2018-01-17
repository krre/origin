#pragma once
#include "Core/Common.h"

namespace Origin {

class RenderState {

public:

    enum class Type {
        Shape2D,
        FreeTypeText,
        SdfText,
        Voxel
    };

    RenderState();
    ~RenderState();

private:

};

} // Origin
