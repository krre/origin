#include "NodeSystem.h"
#include "ECS/Components/NodeComponent.h"
#include "ECS/EntityManager.h"
#include <algorithm>

namespace Origin {

NodeSystem::NodeSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Node;
}

void NodeSystem::process(float dt) {
    for (const auto& entity : entityManager->getEntities()) {
        NodeComponent* nc = static_cast<NodeComponent*>(entity.second->components[Component::Type::Node].get());
        if (nc) {

        }
    }
}

void NodeSystem::addChild(EntityId parent, EntityId child) {
    for (const auto& parentEntity : entityManager->getEntities()) {
        if (parentEntity.first == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity.second->components[Component::Type::Node].get());
            ncParent->children.push_back(child);
            for (const auto& childEntity: entityManager->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity.second->components[Component::Type::Node].get());
                ncChild->parent = parent;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChild(EntityId parent, EntityId child) {
    for (const auto& parentEntity : entityManager->getEntities()) {
        if (parentEntity.first == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity.second->components[Component::Type::Node].get());
            ncParent->children.erase(std::remove(ncParent->children.begin(), ncParent->children.end(), child), ncParent->children.end());
            for (const auto& childEntity: entityManager->getEntities()) {
                NodeComponent* ncChild = static_cast<NodeComponent*>(childEntity.second->components[Component::Type::Node].get());
                ncChild->parent = 0;
                break;
            }
            break;
        }
    }
}

void NodeSystem::removeChildren(EntityId parent) {
    for (const auto& parentEntity : entityManager->getEntities()) {
        if (parentEntity.first == parent) {
            NodeComponent* ncParent = static_cast<NodeComponent*>(parentEntity.second->components[Component::Type::Node].get());
            for (const auto& child: ncParent->children) {
                removeChild(parent, child);
            }
            break;
        }
    }
}

} // Origin
