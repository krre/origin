#include "Game.h"
#include "../Scene/Scene.h"
#include "App.h"
#include "../Graphics/Model/Plane.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include <SDL_keycode.h>
#include <glm/ext.hpp>

extern App* app;
extern Event* event;
extern Input* input;

Game::Game() : prevMousePos(-1) {

}

void Game::create() {
    shared_ptr<View> playerView = shared_ptr<View>(new View());
    ::app->getViewport()->addView(playerView);
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());
    playerView->setScene(scene);

    shared_ptr<Plane> plane = shared_ptr<Plane>(new Plane(100, 100));
    scene->setRoot(plane);

    camera = ::app->getViewport()->getView(0)->getCamera();
    camera->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
    pitch = -35.0f;

    ::event->update.connectMember(&Game::update, this, std::placeholders::_1);
}

void Game::cameraMove(float dt) {
    const float MOVE_SPEED = 1.0f;
    const float ROTATE_SPEED = 0.2f;

    glm::ivec2 mousePos = ::input->getMousePos();
    if (prevMousePos.x != -1) {
        glm::ivec2 mouseDelta = mousePos - prevMousePos;

        yaw += ROTATE_SPEED * mouseDelta.x;
        yaw = fmod(yaw, 360.0f);

        pitch += ROTATE_SPEED * mouseDelta.y;
        pitch = glm::clamp(pitch, -80.0f, 80.0f);

        glm::quat rotation = glm::toQuat(glm::eulerAngleYX(glm::radians(yaw), glm::radians(pitch)));
        camera->setRotation(rotation);
    }

    prevMousePos = mousePos;

    if (::input->isKeyPressed(SDLK_w)) {
        camera->translate(glm::vec3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * dt);
    } else if (::input->isKeyPressed(SDLK_s)) {
        camera->translate(glm::vec3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * dt);
    } else if (::input->isKeyPressed(SDLK_a)) {
        camera->translate(glm::vec3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    } else if (::input->isKeyPressed(SDLK_d)) {
        camera->translate(glm::vec3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    }
}

void Game::update(float dt) {
    cameraMove(dt);
}
