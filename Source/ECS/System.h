#pragma once
#include "../Core/Object.h"
#include "Entity.h"
#include <vector>

enum class SystemType {
    Camera,
    Input,
    MotionController,
    Node,
    None,
    Render,
    Transform
};

class Engine;

class System : public Object {

public:
    System();

    virtual void process(float dt) = 0;

    SystemType getType() const { return type; }

    bool setActive(bool active);
    bool getActive() const { return active; }

protected:
    SystemType type = SystemType::None;
    bool active = true;
    static Engine* engine;
};
