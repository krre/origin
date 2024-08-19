#pragma once
#include "Layout.h"

class LinearLayout : public Layout {
public:
    enum class Direction {
        Horizontal,
        Vertical
    };

    LinearLayout(Direction direction, Control* parent = nullptr);

private:
    void updateContentPostion() override;
    Direction m_direction;
};
