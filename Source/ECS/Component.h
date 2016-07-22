#pragma once
#include "../Core/Object.h"

class Component : public Object {

public:
    enum class Type {
        Camera,
        Empty,
        Input,
        Light,
        Material,
        Mesh,
        MotionController,
        Movement,
        Node,
        Render,
        Transform
    };

    Component();
    Component::Type getType() const { return type; }
    bool enable = true;
    bool dirty = false;

protected:
    Component::Type type = Component::Type::Empty;
};
