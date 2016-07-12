#include "Game.h"
#include "../Scene/Scene.h"
#include "App.h"
#include "../Debug/Console.h"
#include "../Debug/DebugHUD.h"
#include "../UI/Toast.h"
#include "../Graphics/Mesh/Plane.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include "../ECS/Engine.h"
#include "../ECS/System.h"
#include "../ECS/EntityBuilder.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/Systems.h"
#include <SDL_keycode.h>
#include <glm/ext.hpp>
#include <ctime>

Game::Game() {

}

void Game::create() {
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Avatar
    Entity* avatar = EntityBuilder::avatar();
    Engine::getInstance()->addEntity(avatar);
    InputSystem* inputSystem = static_cast<InputSystem*>(Engine::getInstance()->getSystem(SystemType::Input));\
    inputSystem->setActiveEntity(avatar);

    Entity* avatarCamera = EntityBuilder::camera();
    TransformSystem* avatarCameraTransformSystem = static_cast<TransformSystem*>(Engine::getInstance()->getSystem(SystemType::Transform));
    avatarCameraTransformSystem->translate(avatarCamera, glm::vec3(0.0f, 0.5f, 0.0f));
    NodeSystem* nodeSystem = static_cast<NodeSystem*>(Engine::getInstance()->getSystem(SystemType::Node));
    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());

    // Ground
    Engine::getInstance()->addEntity(EntityBuilder::ground());

    std::shared_ptr<Scene> scene = std::shared_ptr<Scene>(new Scene());
    App::getInstance()->getViewport()->setScene(scene);
    App::getInstance()->getViewport()->setBackgroundColor(glm::vec4(0.25, 0.2, 0.2, 1.0));

    std::shared_ptr<Plane> plane = std::shared_ptr<Plane>(new Plane(1, 1));
    scene->setRoot(plane);

    camera = App::getInstance()->getViewport()->getCamera();
    camera->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
    pitch = -35.0f;

    Event::getInstance()->keyPress.connectMember(&Game::keyPress, this, std::placeholders::_1);
    Event::getInstance()->mouseButtonAction.connectMember(&Game::mouseButtonAction, this, std::placeholders::_1);
}

void Game::load() {

}

void Game::save() {

}

void Game::setState(Game::State state) {
    this->state = state;
}

void Game::cameraMove(float dt) {
    if (state != PLAY) return;

    const float MOVE_SPEED = 1.0f;
    const float ROTATE_SPEED = 0.1f;

    glm::ivec2 relMousePos = Input::getInstance()->getRelMousePos();
    yaw += ROTATE_SPEED * relMousePos.x;
    yaw = fmod(yaw, 360.0f);

    pitch -= ROTATE_SPEED * relMousePos.y;
    pitch = glm::clamp(pitch, -80.0f, 80.0f);

    glm::quat rotation = glm::toQuat(glm::eulerAngleYX(glm::radians(yaw), glm::radians(pitch)));
    camera->setRotation(rotation);

    if (Input::getInstance()->isKeyPressed(SDLK_w)) {
        camera->translate(glm::vec3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_s)) {
        camera->translate(glm::vec3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_a)) {
        camera->translate(glm::vec3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_d)) {
        camera->translate(glm::vec3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    }
}

void Game::keyPress(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
    case SDLK_ESCAPE:
        if (state == PLAY) {
            state = PAUSE;
            SDL_SetRelativeMouseMode(SDL_FALSE);
        } else if (state == CONSOLE) {
            Console::getInstance()->setVisible(false);
            state = PLAY;
        }
        break;

    case SDLK_F5:
        DebugHUD::getInstance()->trigger();
        break;

    case SDLK_F10:
        toggleFullScreen();
        break;

    case SDLK_F12:
        saveScreenshot();
        break;

    case SDLK_SLASH:
        if (state == PLAY) {
            Console::getInstance()->setVisible(true);
            state = CONSOLE;
        }
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
    bool isFullscreen = SDL_GetWindowFlags(App::getInstance()->getWindow()) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(App::getInstance()->getWindow(), isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(isFullscreen);
}

void Game::saveScreenshot() {
    time_t t = std::time(0);   // get time now
    struct tm * now = std::localtime(&t);
    std::string path = "Screenshot saved to " +
            App::getAbsolutePath() +
            App::getPathSeparator() + "Screenshot" + App::getPathSeparator() +
            std::to_string(now->tm_year + 1900) + "-" +
            std::to_string(now->tm_mon + 1) + "-" +
            std::to_string(now->tm_mday) + "_" +
            std::to_string(now->tm_hour) + "-" +
            std::to_string(now->tm_min) + "-" +
            std::to_string(now->tm_sec) + ".png";
    Toast::getInstance()->showToast(path);
}
