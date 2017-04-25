#pragma once
#include "Core/Object.h"
#include "ECSTypes.h"

class Component : public Object {

public:
    Component();
    ComponentType getType() const { return type; }
    bool enable = true;
    bool dirty = false;

protected:
    ComponentType type = ComponentType::Empty;
};
