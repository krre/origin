#include "Player.h"

Player::Player() {
    addComponent(ComponentType::Node);
    addComponent(ComponentType::Camera);
    addComponent(ComponentType::Transform);
}
