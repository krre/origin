#pragma once
#include "../System.h"
#include <glm/ext.hpp>

using namespace glm;

class TransformSystem : public System {

public:
    TransformSystem();
    void process(float dt) override;

    void setPosition(Entity* entity, vec3& position);
    void setRotation(Entity* entity, float angle, vec3& axis);
    void setRotation(Entity* entity, quat& rotation);
    void setScale(Entity* entity, vec3& scale);

    void translate(Entity* entity, const vec3& delta, bool local = true);
    void rotate(Entity* entity, quat& delta);
    void scale(Entity* entity, vec3& delta);
};
