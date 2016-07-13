#include "Model.h"

Model::Model() {

}

void Model::draw(float dt) {

}

void Model::setMaterial(Material* material) {
    this->material = material;
}

void Model::setMesh(Mesh* mesh) {
    this->mesh = mesh;
}
