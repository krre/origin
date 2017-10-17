#pragma once
#include "UITypes.h"
#include "Layout.h"

class LinearLayout : public Layout {

public:
    LinearLayout(Direction direction);

private:
    void updateContentPostion() override;
    Direction direction;
};
