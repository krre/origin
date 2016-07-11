#pragma once
#include "../Core/Object.h"
#include <list>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Node : public Object {

public:
    Node();

    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);
    void removeChildren() { nodes.clear(); }

    virtual void draw() {}

    void setPosition(const glm::vec3& position);
    const glm::vec3 getPosition() const { return position; }

    void setRotation(float angle, const glm::vec3& axis);
    void setRotation(const glm::quat& rotation);
    const glm::quat getRotation() const { return rotation; }

    void setScale(const glm::vec3& scale);

    void translate(const glm::vec3& delta, bool local = true);
    void rotate(const glm::quat& delta);
    void scale(const glm::vec3& scale);

    void lookAt(const glm::vec3& center);

    const glm::mat4& getModelMatrix();

private:
    void updateModelMatrix();
    std::list<std::shared_ptr<Node>> nodes;
    glm::mat4 modelMatrix;
    glm::mat4 translationMatrix;
    glm::mat4 rotationMatrix;
    glm::mat4 scaleMatrix;
    glm::quat rotation;
    glm::vec3 position;
    bool dirty = false;
};
