#include "LinearLayout.h"

namespace Origin {

LinearLayout::LinearLayout(Direction direction) :
    direction(direction) {

}

void LinearLayout::updateContentPostion() {
    int i = 0;
    for (const auto& control : controls) {
        if (direction == Direction::VERICAL) {
            control->setPosition({ position.x, position.y + i * ((int)control->getSize().width + spacing) });
            i++;
        } else {
            control->setPosition({ position.x + i * ((int)control->getSize().height + spacing), position.y });
            i++;
        }
    }
}

} // Origin
