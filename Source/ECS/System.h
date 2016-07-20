#pragma once
#include "../Core/Object.h"
#include "Entity.h"
#include <vector>

class Engine;

class System : public Object {

public:
    enum class Type {
        None,
        Input,
        Render,
        Transform,
        Node,
        MotionController
    };

    System();

    virtual void process(float dt) = 0;

    Type getType() const { return type; }

    bool setActive(bool active);
    bool getActive() const { return active; }

protected:
    Type type = Type::None;
    bool active = true;
    static Engine* engine;
};
