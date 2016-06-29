#include "Ground.h"
#include "../ECS/Components/NodeComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/RenderComponent.h"

Ground::Ground() {
    addComponent<NodeComponent>();
    addComponent<RenderComponent>();
    addComponent<TransformComponent>();
}
