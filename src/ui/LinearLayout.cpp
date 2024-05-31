#include "LinearLayout.h"
#include "Control.h"

LinearLayout::LinearLayout(Direction direction, Control* parent) :
    Layout(parent),
    direction(direction) {
}

void LinearLayout::updateContentPostion() {
    m_contentWidth = 0;
    m_contentHeight = 0;
    int positionX = m_position.x;
    int positionY = m_position.y;
    for (const auto& child : getChildren()) {
        Control* control = static_cast<Control*>(child);
        if (direction == Direction::Vertical) {
            control->move(positionX, positionY);
            positionY += control->contentHeight() + spacing();
            m_contentWidth = std::max(m_contentWidth, control->contentWidth());
            m_contentHeight += control->contentHeight() + spacing();
        } else {
            control->move(positionX, positionY);
            positionX += control->contentWidth() + spacing();
            m_contentWidth += control->contentWidth() + spacing();
            m_contentHeight = std::max(m_contentHeight, control->contentHeight());
        }
    }

    // Remove last spacing
    if (getChildren().size()) {
        if (direction == Direction::Vertical) {
            m_contentHeight -= spacing();
        } else {
            m_contentWidth -= spacing();
        }
    }
}
