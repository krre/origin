#include "Model.h"

Model::Model() {

}

void Model::draw(float dt) {
    mesh->draw();
}

void Model::setMaterial(std::shared_ptr<Material> material) {
    this->material = material;
}

void Model::setMesh(std::shared_ptr<Mesh> mesh) {
    this->mesh = mesh;
}
