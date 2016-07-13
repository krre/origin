#pragma once
#include "Drawable.h"
#include "Mesh.h"
#include "Material.h"

class Model : public Drawable {

public:
    Model();
    void draw(float dt) override;

    Material* getMaterial() const { return material; }
    void setMaterial(Material* material);

    Mesh* getMesh() const { return mesh; }
    void setMesh(Mesh* mesh);

private:
    Mesh* mesh;
    Material* material;
};
