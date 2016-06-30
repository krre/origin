#pragma once
#include "../Core/Object.h"
#include <list>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

class Node : public Object {

public:
    Node();

    void addChild(shared_ptr<Node> child);
    void removeChild(shared_ptr<Node> child);
    void removeChildren() { nodes.clear(); }

    virtual void draw() {}

    void setPosition(const vec3& position);
    const vec3 getPosition() const { return position; }

    void setRotation(float angle, const vec3& axis);
    void setRotation(const quat& rotation);
    const quat getRotation() const { return rotation; }

    void setScale(const vec3& scale);

    void translate(const vec3& delta, bool local = true);
    void rotate(const quat& delta);
    void scale(const vec3& scale);

    void lookAt(const vec3& center);

    const mat4& getModelMatrix();

private:
    void updateModelMatrix();
    list<shared_ptr<Node>> nodes;
    mat4 modelMatrix;
    mat4 translationMatrix;
    mat4 rotationMatrix;
    mat4 scaleMatrix;
    quat rotation;
    vec3 position;
    bool dirty = false;
};
