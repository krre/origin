#include "NodeSystem.h"
#include "../Components/NodeComponent.h"
#include "../Engine.h"

NodeSystem::NodeSystem() {
    type = SystemType::Node;
}

void NodeSystem::process(float dt) {
    for (auto entity: Engine::getInstance()->getEntities()) {
        NodeComponent* nc = static_cast<NodeComponent*>(entity->getComponent(ComponentType::Node));
        if (nc) {
//            print(nc);
        }
    }
}
