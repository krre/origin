#pragma once
#include "../Component.h"
#include "../Graphics/Mesh.h"

class MeshComponent : public Component {

public:
    MeshComponent();
    std::shared_ptr<Mesh> mesh;
};
