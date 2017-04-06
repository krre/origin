#include "LinearLayout.h"

LinearLayout::LinearLayout(Direction direction) :
    direction(direction) {

}

void LinearLayout::updateContentPostion() {
    int i = 0;
    for (auto& control : controls) {
        if (direction == VERICAL) {
            control->setPosition(glm::vec2(position.x, position.y + i * (control->getSize().y + spacing)));
            i++;
        } else {
            control->setPosition(glm::vec2(position.x + i * (control->getSize().x + spacing), position.y));
            i++;
        }
    }
}
