#include "LinearLayout.h"
#include "Control.h"

namespace Origin {

LinearLayout::LinearLayout(Direction direction, Control* parent) :
    Layout(parent),
    direction(direction) {
}

void LinearLayout::updateContentPostion() {
    contentWidth = 0;
    contentHeight = 0;
    int positionX = position.x;
    int positionY = position.y;
    for (const auto& child : getChildren()) {
        Control* control = static_cast<Control*>(child);
        if (direction == Direction::Vertical) {
            control->move(positionX, positionY);
            positionY += control->getContentHeight() + spacing;
            contentWidth = std::max(contentWidth, control->getContentWidth());
            contentHeight += control->getContentHeight() + spacing;
        } else {
            control->move(positionX, positionY);
            positionX += control->getContentWidth() + spacing;
            contentWidth += control->getContentHeight() + spacing;
            contentHeight = std::max(contentHeight, control->getContentHeight());
        }
    }

    // Remove last spacing
    if (getChildren().size()) {
        if (direction == Direction::Vertical) {
            contentHeight -= spacing;
        } else {
            contentWidth -= spacing;
        }
    }
}

} // Origin
