#include "Ground.h"
#include "../ECS/Components/NodeComponent.h"
#include "../ECS/Components/RenderComponent.h"
#include "../ECS/Components/TransformComponent.h"

Ground::Ground() {
    addComponent(ComponentType::Node);
    addComponent(ComponentType::Render);
    addComponent(ComponentType::Transform);
}
