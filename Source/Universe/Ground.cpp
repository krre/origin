#include "Ground.h"

Ground::Ground() {
    addComponent(ComponentType::Node);
    addComponent(ComponentType::Render);
    addComponent(ComponentType::Transform);
}
