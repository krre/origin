#include "NodeSystem.h"
#include "../Components/NodeComponent.h"
#include "../Engine.h"
#include <algorithm>

NodeSystem::NodeSystem() {
    type = SystemType::Node;
}

void NodeSystem::process(float dt) {
    for (auto entity: engine->getEntities()) {
        NodeComponent* nc = static_cast<NodeComponent*>(entity->components[ComponentType::Node].get());
        if (nc) {

        }
    }
}

void NodeSystem::addChild(EntityId parent, EntityId child) {
    for (auto parentEntity: engine->getEntities()) {
        if (parentEntity->getId() == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity->components[ComponentType::Node].get());
            ncParent->children.push_back(child);
            for (auto childEntity: engine->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity->components[ComponentType::Node].get());
                ncChild->parent = parent;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChild(EntityId parent, EntityId child) {
    for (auto parentEntity: engine->getEntities()) {
        if (parentEntity->getId() == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity->components[ComponentType::Node].get());
            ncParent->children.erase(std::remove(ncParent->children.begin(), ncParent->children.end(), child), ncParent->children.end());
            for (auto childEntity: engine->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity->components[ComponentType::Node].get());
                ncChild->parent = 0;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChildren(EntityId parent) {
    for (auto parentEntity: engine->getEntities()) {
        if (parentEntity->getId() == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity->components[ComponentType::Node].get());
            for (auto child: ncParent->children) {
                removeChild(parent, child);
            }
            break;
        }
    }
}
