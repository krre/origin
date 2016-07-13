#pragma once
#include "Drawable.h"
#include "Mesh.h"
#include "Material.h"

class Model : public Drawable {

public:
    Model();
    void draw(float dt) override;

    std::shared_ptr<Material> getMaterial() const { return material; }
    void setMaterial(std::shared_ptr<Material> material);

    std::shared_ptr<Mesh> getMesh() const { return mesh; }
    void setMesh(std::shared_ptr<Mesh> mesh);

private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
};
