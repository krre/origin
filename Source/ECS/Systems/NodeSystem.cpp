#include "NodeSystem.h"
#include "../Components/NodeComponent.h"
#include "../Engine.h"
#include <algorithm>

NodeSystem::NodeSystem() {
    type = System::Type::Node;
}

void NodeSystem::process(float dt) {
    for (auto entity: Engine::getInstance()->getEntities()) {
        NodeComponent* nc = static_cast<NodeComponent*>(entity->getComponent(Component::Type::Node));
        if (nc) {

        }
    }
}

void NodeSystem::addChild(EntityId parent, EntityId child) {
    for (auto parentEntity: Engine::getInstance()->getEntities()) {
        if (parentEntity->getId() == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity->getComponent(Component::Type::Node));
            ncParent->children.push_back(child);
            for (auto childEntity: Engine::getInstance()->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity->getComponent(Component::Type::Node));
                ncChild->parent = parent;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChild(EntityId parent, EntityId child) {
    for (auto parentEntity: Engine::getInstance()->getEntities()) {
        if (parentEntity->getId() == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity->getComponent(Component::Type::Node));
            ncParent->children.erase(std::remove(ncParent->children.begin(), ncParent->children.end(), child), ncParent->children.end());
            for (auto childEntity: Engine::getInstance()->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity->getComponent(Component::Type::Node));
                ncChild->parent = 0;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChildren(EntityId parent) {
    for (auto parentEntity: Engine::getInstance()->getEntities()) {
        if (parentEntity->getId() == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity->getComponent(Component::Type::Node));
            for (auto child: ncParent->children) {
                removeChild(parent, child);
            }
            break;
        }
    }
}
