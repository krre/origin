#pragma once

namespace Origin {

enum class SystemType {
    Camera,
    Input,
    MovementController,
    Node,
    None,
    Octree,
    Physics,
    Render,
    Transform
};

enum class ComponentType {
    Camera,
    Empty,
    Light,
    Material,
    Mesh,
    MovementController,
    Movement,
    Node,
    Octree,
    Physics,
    Render,
    Transform
};

} // Origin
