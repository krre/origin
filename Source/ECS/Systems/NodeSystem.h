#pragma once
#include "../System.h"
#include "../Entity.h"

class NodeSystem : public System {

public:
    NodeSystem();
    void process(float dt) override;

    void addChild(EntityId parent, EntityId child);
    void removeChild(EntityId parent, EntityId child);
    void removeChildren(EntityId parent);
};
