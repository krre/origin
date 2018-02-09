#include "LinearLayout.h"
#include "Control.h"

namespace Origin {

LinearLayout::LinearLayout(Direction direction, Control* parent) :
    Layout(parent),
    direction(direction) {
}

void LinearLayout::updateContentPostion() {
    int i = 0;
    contentWidth = 0;
    contentHeight = 0;
    for (const auto& control : controls) {
        if (direction == Direction::Vertical) {
            control->move(position.x, position.y + i * (control->getContentHeight() + spacing));
            contentWidth = std::max(contentWidth, control->getContentWidth());
            contentHeight += control->getContentHeight() + spacing;
        } else {
            control->move(position.x + i * (control->getContentWidth() + spacing), position.y);
            contentWidth += control->getContentHeight() + spacing;
            contentHeight = std::max(contentHeight, control->getContentHeight());
        }

        i++;
    }

    // Remove last spacing
    if (controls.size()) {
        if (direction == Direction::Vertical) {
            contentHeight -= spacing;
        } else {
            contentWidth -= spacing;
        }
    }
}

} // Origin
