#pragma once
#include "Layout.h"

class LinearLayout : public Layout {

public:
    enum Direction {
        HORIZONTAL,
        VERICAL
    };

    LinearLayout(Direction direction);

private:
    void updateContentPostion() override;
    Direction direction;
};
