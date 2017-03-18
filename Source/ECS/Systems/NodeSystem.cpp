#include "NodeSystem.h"
#include "../Components/NodeComponent.h"
#include "../EntityManager.h"
#include <algorithm>

NodeSystem::NodeSystem() {
    type = SystemType::Node;
}

void NodeSystem::process(float dt) {
    for (auto& entity : entityManager->getEntities()) {
        NodeComponent* nc = static_cast<NodeComponent*>(entity.second->components[ComponentType::Node].get());
        if (nc) {

        }
    }
}

void NodeSystem::addChild(EntityId parent, EntityId child) {
    for (auto& parentEntity : entityManager->getEntities()) {
        if (parentEntity.first == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity.second->components[ComponentType::Node].get());
            ncParent->children.push_back(child);
            for (auto& childEntity: entityManager->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity.second->components[ComponentType::Node].get());
                ncChild->parent = parent;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChild(EntityId parent, EntityId child) {
    for (auto& parentEntity : entityManager->getEntities()) {
        if (parentEntity.first == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity.second->components[ComponentType::Node].get());
            ncParent->children.erase(std::remove(ncParent->children.begin(), ncParent->children.end(), child), ncParent->children.end());
            for (auto& childEntity: entityManager->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity.second->components[ComponentType::Node].get());
                ncChild->parent = 0;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChildren(EntityId parent) {
    for (auto& parentEntity : entityManager->getEntities()) {
        if (parentEntity.first == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity.second->components[ComponentType::Node].get());
            for (auto& child: ncParent->children) {
                removeChild(parent, child);
            }
            break;
        }
    }
}
