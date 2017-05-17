#pragma once
#include "Layout.h"
#include "UITypes.h"

class LinearLayout : public Layout {

public:
    LinearLayout(Direction direction);

private:
    void updateContentPostion() override;
    Direction direction;
};
