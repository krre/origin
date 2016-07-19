#pragma once
#include "../System.h"
#include <glm/ext.hpp>

class TransformSystem : public System {

public:
    TransformSystem();
    void process(float dt) override;

    void setPosition(Entity* entity, glm::vec3& position);
    void setRotation(Entity* entity, float angle, glm::vec3& axis);
    void setRotation(std::shared_ptr<Entity> entity, glm::quat& rotation);
    void setScale(std::shared_ptr<Entity> entity, glm::vec3& scale);

    void translate(std::shared_ptr<Entity> entity, const glm::vec3& delta, bool local = true);
    void rotate(std::shared_ptr<Entity> entity, glm::quat& delta);
    void scale(std::shared_ptr<Entity> entity, glm::vec3& delta);
};
