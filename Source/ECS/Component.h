#pragma once

namespace Origin {

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
    Type getType() const { return type; }
    bool enable = true;
    bool dirty = false;

protected:
    Type type = Type::Empty;
};

} // Origin
