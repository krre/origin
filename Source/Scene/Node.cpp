#include "Node.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

Node::Node() :
    translationMatrix(1.0f),
    rotationMatrix(1.0f),
    scaleMatrix(1.0f),
    modelMatrix(1.0f) {
}

void Node::addChild(shared_ptr<Node> child) {
    nodes.push_back(child);
}

void Node::removeChild(shared_ptr<Node> child) {
    nodes.remove(child);
}

void Node::setPosition(const vec3& position) {
    translationMatrix = glm::translate(mat4(1.0f), position);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::setRotation(float angle, const vec3& axis) {
    rotationMatrix = glm::rotate(mat4(1.0f), angle, axis);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::setRotation(const quat& rotation) {
    this->rotation = rotation;
    rotationMatrix = glm::toMat4(rotation);
    modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
}

void Node::setScale(const vec3& scale) {
    scaleMatrix = glm::scale(mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::translate(const vec3& vector) {
    translationMatrix = glm::translate(translationMatrix, vector);
    modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
}

void Node::rotate(float angle, const vec3& axis) {
    rotationMatrix = glm::rotate(rotationMatrix, angle, axis);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::scale(const vec3& scale) {
    scaleMatrix = glm::scale(scaleMatrix, scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::lookAt(const vec3& center) {
    modelMatrix = glm::lookAt(
        glm::vec3(0, 1, 2), // Camera position in World Space
        center, // looks at center
        glm::vec3(0, 1, 0)  // Head is up (set to 0, -1, 0 to look upside-down)
    );
}
