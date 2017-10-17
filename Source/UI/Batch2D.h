#pragma once
#include "Core/Object.h"
#include "UITypes.h"

class Batch2D : public Object {

public:
    Batch2D();
    ControlType controlType = ControlType::USUAL;
};
