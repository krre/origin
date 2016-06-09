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

    void setPosition(float x, float y, float z);
    void setRotation(float angle);
    void setScale(float scale);

private:
    list<shared_ptr<Node>> nodes;
    glm::mat4 matrix;
};
