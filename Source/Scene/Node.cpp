#include "Node.h"
#include <glm/gtc/matrix_transform.hpp>

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

void Node::setPosition(const glm::vec3& position) {
    translationMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::setRotation(float angle, const glm::vec3& axis) {
    rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::setScale(const glm::vec3& scale) {
    scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::translate(const glm::vec3& vector) {
    translationMatrix = glm::translate(translationMatrix, vector);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::rotate(float angle, const glm::vec3& axis) {
    rotationMatrix = glm::rotate(rotationMatrix, angle, axis);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Node::scale(const glm::vec3& scale) {
    scaleMatrix = glm::scale(scaleMatrix, scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}
