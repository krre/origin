#pragma once
#include "../Core/Object.h"

class Component : public Object {

public:
    enum class Type {
        Camera,
        Empty,
        Input,
        Node,
        Render,
        Transform,
        Movement,
        Mesh,
        Material,
        MotionController
    };


    Component();
    Component::Type getType() const { return type; }
    bool enable = true;
    bool dirty = false;

protected:
    Component::Type type = Component::Type::Empty;
};
