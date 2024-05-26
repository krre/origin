#pragma once

class Component {

public:

    enum class Type {
        Camera,
        Empty,
        Light,
        Material,
        Mesh,
        MovementController,
        Movement,
        Octree,
        Physics,
        Render,
        Transform
    };

    Component();
    virtual Type getType() const = 0;
    bool enable = true;
    bool dirty = false;
};
