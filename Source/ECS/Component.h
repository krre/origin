#pragma once
#include "../Core/Object.h"

class Component : public Object {

public:

    enum Type {
        Empty,
        Transform,
        Camera
    };

    Component();
    Type getType() const { return type; }

protected:
    Type type = Empty;
};
