#pragma once
#include "ECS/Entity.h"
#include "ECS/Component.h"
#include <vector>

namespace Origin {

class NodeComponent : public Component {

public:
    NodeComponent() { type = Component::Type::Node; }
    EntityId parent = 0;
    std::vector<EntityId> children;
};

} // Origin
