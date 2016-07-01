#pragma once
#include "../Component.h"
#include "../Graphics/Mesh.h"

class MeshComponent : public Component {

public:
    MeshComponent();
    Mesh* mesh;
};
