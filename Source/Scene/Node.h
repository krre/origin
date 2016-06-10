#pragma once
#include "../Core/Object.h"
#include <list>
#include <glm/glm.hpp>

class Node : public Object {

public:
    Node();

    void addChild(shared_ptr<Node> child);
    void removeChild(shared_ptr<Node> child);
    void removeChildren() { nodes.clear(); }

    virtual void draw() {}

    void setPosition(const glm::vec3& position);
    void setRotation(float angle);
    void setScale(float scale);

    void translate(const glm::vec3& vector);

    const glm::mat4& getModelMatrix() const { return modelMatrix; }

protected:
    glm::mat4 modelMatrix;

private:
    list<shared_ptr<Node>> nodes;
    glm::mat4 translationMatrix;
    glm::mat4 rotationMatrix;
    glm::mat4 scaleMatrix;
};
