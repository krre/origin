#include "Game.h"
#include "../Scene/Scene.h"
#include "App.h"
#include "../Graphics/Model/Plane.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include <SDL_keycode.h>
#include <glm/ext.hpp>

extern App* app;

Game::Game() {

}

void Game::create() {
    SDL_SetRelativeMouseMode(SDL_TRUE);

    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());
    ::app->getViewport()->setScene(scene);
    ::app->getViewport()->setBackgroundColor(glm::vec4(0.25, 0.2, 0.2, 1.0));

    shared_ptr<Plane> plane = shared_ptr<Plane>(new Plane(1, 1));
    scene->setRoot(plane);

    camera = ::app->getViewport()->getCamera();
    camera->setPosition(vec3(0.0f, 0.5f, 0.0f));
    pitch = -35.0f;

    Event::getInstance()->update.connectMember(&Game::update, this, std::placeholders::_1);
    Event::getInstance()->keyPress.connectMember(&Game::keyPress, this, std::placeholders::_1);
    Event::getInstance()->mouseButtonAction.connectMember(&Game::mouseButtonAction, this, std::placeholders::_1);
}

void Game::cameraMove(float dt) {
    if (state == PAUSE) return;

    const float MOVE_SPEED = 1.0f;
    const float ROTATE_SPEED = 0.1f;

    ivec2 relMousePos = Input::getInstance()->getRelMousePos();
    yaw += ROTATE_SPEED * relMousePos.x;
    yaw = fmod(yaw, 360.0f);

    pitch -= ROTATE_SPEED * relMousePos.y;
    pitch = clamp(pitch, -80.0f, 80.0f);

    quat rotation = toQuat(eulerAngleYX(radians(yaw), radians(pitch)));
    camera->setRotation(rotation);

    if (Input::getInstance()->isKeyPressed(SDLK_w)) {
        camera->translate(vec3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_s)) {
        camera->translate(vec3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_a)) {
        camera->translate(vec3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_d)) {
        camera->translate(vec3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    }
}

void Game::update(float dt) {
    cameraMove(dt);
    engine.update(dt);
}

void Game::keyPress(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
    case SDLK_ESCAPE:
//        ::app->quit();
        state = PAUSE;
        SDL_SetRelativeMouseMode(SDL_FALSE);
        break;

    case SDLK_F3:
        saveScreenshot();
        break;

    case SDLK_F10:
        toggleFullScreen();
        break;
    default:
        break;
    }
}

void Game::mouseButtonAction(const SDL_MouseButtonEvent& event) {
    if (state == PAUSE) {
        state = PLAY;
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
}

void Game::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(::app->getWindow()) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(::app->getWindow(), isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(isFullscreen);
}

void Game::saveScreenshot() {
    print("Screenshot saved to " << App::getAbsolutePath() + "/Screenshot");
}
