#pragma once
#include "../System.h"
#include <glm/ext.hpp>

class TransformSystem : public System {

public:
    TransformSystem();
    void process(float dt) override;
    void update(Entity* entity);

    void setPosition(Entity* entity, const glm::vec3& position);
    void setRotation(Entity* entity, float angle, const glm::vec3& axis);
    void setRotation(Entity* entity, const glm::quat& rotation);
    void setScale(Entity* entity, float scale);

    void setPitch(Entity* entity, float pitch);

    void translate(Entity* entity, const glm::vec3& delta, bool local = true);
    void rotate(Entity* entity, const glm::quat& delta);
    void scale(Entity* entity, float delta);

    void lookAt(Entity* entity, const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);
};
