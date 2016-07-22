#pragma once
#include "../Component.h"
#include "../Graphics/Mesh.h"

class MeshComponent : public Component {

public:
    MeshComponent() { type = ComponentType::Mesh; }
    std::shared_ptr<Mesh> mesh;
};
