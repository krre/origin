#include "LinearLayout.h"

LinearLayout::LinearLayout(Direction direction) :
    direction(direction) {

}

void LinearLayout::updateContentPostion() {
    int i = 0;
    for (auto& control : controls) {
        if (direction == Direction::VERICAL) {
            control->setPosition({ position.x, position.y + i * (control->getSize().width + spacing) });
            i++;
        } else {
            control->setPosition({ position.x + i * (control->getSize().height + spacing), position.y });
            i++;
        }
    }
}
