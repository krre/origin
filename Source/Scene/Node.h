#pragma once
#include "../Core/Object.h"
#include <list>
#include <glm/glm.hpp>

using namespace glm;

class Node : public Object {

public:
    Node();

    void addChild(shared_ptr<Node> child);
    void removeChild(shared_ptr<Node> child);
    void removeChildren() { nodes.clear(); }

    virtual void draw() {}

    void setPosition(const vec3& position);
    void setRotation(float angle, const vec3& axis);
    void setRotation(const quat& rotation);
    void setScale(const vec3& scale);

    void translate(const vec3& vector);
    void rotate(float angle, const vec3& axis);
    void scale(const vec3& scale);

    void lookAt(const vec3& center);

    const mat4& getModelMatrix() const { return modelMatrix; }

protected:
    mat4 modelMatrix;

private:
    list<shared_ptr<Node>> nodes;
    mat4 translationMatrix;
    mat4 rotationMatrix;
    mat4 scaleMatrix;
};
