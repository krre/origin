#include "Node.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <algorithm>

Node::Node() :
    translationMatrix(1.0f),
    rotationMatrix(1.0f),
    scaleMatrix(1.0f),
    modelMatrix(1.0f) {
}

void Node::addChild(std::shared_ptr<Node> child) {
    nodes.push_back(child);
}

void Node::removeChild(std::shared_ptr<Node> child) {
    nodes.erase(std::remove(nodes.begin(), nodes.end(), child), nodes.end());
}

void Node::setPosition(const glm::vec3& position) {
    this->position = position;
    dirty = true;
}

void Node::setRotation(float angle, const glm::vec3& axis) {
    rotation = toQuat(glm::rotate(glm::mat4(1.0f), angle, axis));
    dirty = true;
}

void Node::setRotation(const glm::quat& rotation) {
    this->rotation = rotation;
    dirty = true;
}

void Node::setScale(const glm::vec3& scale) {
    scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    dirty = true;
}

void Node::translate(const glm::vec3& delta, bool local) {
    if (local) {
        position += rotation * delta;
    } else {
        position += delta;
    }

    dirty = true;
}

void Node::rotate(const glm::quat& delta) {
    rotation *= delta;
    dirty = true;
}

void Node::scale(const glm::vec3& scale) {
    scaleMatrix = glm::scale(scaleMatrix, scale);
    dirty = true;
}

void Node::lookAt(const glm::vec3& center) {
    modelMatrix = glm::lookAt(
        glm::vec3(0, 1, 2), // Camera position in World Space
        center, // looks at center
        glm::vec3(0, 1, 0)  // Head is up (set to 0, -1, 0 to look upside-down)
                );
}

const glm::mat4&Node::getModelMatrix() {
    updateModelMatrix();
    return modelMatrix;
}

void Node::updateModelMatrix() {
    if (dirty) {
        translationMatrix = glm::translate(position);
        rotationMatrix = glm::toMat4(rotation);
        modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
        dirty = false;
    }
}
