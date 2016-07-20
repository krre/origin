#include "Game.h"
#include "App.h"
#include "../Debug/Console.h"
#include "../Debug/DebugHUD.h"
#include "../UI/Toast.h"
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
#include <lodepng/lodepng.h>

Game::Game() {

}

void Game::create() {
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Avatar
    auto avatar = EntityBuilder::avatar();
    Engine::getInstance()->addEntity(avatar);

    std::shared_ptr<Entity> avatarCamera = EntityBuilder::camera();
    App::getInstance()->getViewport()->setCurrentCamera(avatarCamera);
    Engine::getInstance()->addEntity(avatarCamera);
    TransformSystem* transformSystem = static_cast<TransformSystem*>(Engine::getInstance()->getSystem(System::Type::Transform).get());
    transformSystem->translate(avatarCamera.get(), glm::vec3(0.0f, 0.5f, 0.0f));
    transformSystem->setPitch(avatarCamera.get(), -35.0);
    NodeSystem* nodeSystem = static_cast<NodeSystem*>(Engine::getInstance()->getSystem(System::Type::Node).get());
    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());

    MotionControllerSystem* motionControllerSystem = static_cast<MotionControllerSystem*>(Engine::getInstance()->getSystem(System::Type::MotionController).get());
    motionControllerSystem->setMoveEntity(avatarCamera.get());
    motionControllerSystem->setRotateEntity(avatarCamera.get());

    // Ground
    Engine::getInstance()->addEntity(EntityBuilder::ground());

    App::getInstance()->getViewport()->setBackgroundColor(glm::vec4(0.25, 0.2, 0.2, 1.0));

    Event::getInstance()->keyPress.connect<Game, &Game::keyPress>(this);
    Event::getInstance()->mouseButtonAction.connect<Game, &Game::mouseButtonAction>(this);
}

void Game::load() {

}

void Game::save() {

}

void Game::setState(Game::State state) {
    this->state = state;
}

void Game::keyPress(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
    case SDLK_ESCAPE:
        if (state == PLAY) {
            state = PAUSE;
            SDL_SetRelativeMouseMode(SDL_FALSE);
            MotionControllerSystem* motionControllerSystem = static_cast<MotionControllerSystem*>(Engine::getInstance()->getSystem(System::Type::MotionController).get());
            motionControllerSystem->setActive(false);
        } else if (state == CONSOLE) {
            MotionControllerSystem* motionControllerSystem = static_cast<MotionControllerSystem*>(Engine::getInstance()->getSystem(System::Type::MotionController).get());
            motionControllerSystem->setActive(true);
            Console::getInstance()->setVisible(false);
            state = PLAY;
        }
        break;

    case SDLK_F5:
        DebugHUD::getInstance()->trigger();
        break;

    case SDLK_F6:
        wireframe = !wireframe;
        break;

    case SDLK_F10:
        // TODO: Incorrect work
//        toggleFullScreen();
        break;

    case SDLK_F12:
        saveScreenshot();
        break;

    case SDLK_SLASH:
        if (state == PLAY) {
            MotionControllerSystem* motionControllerSystem = static_cast<MotionControllerSystem*>(Engine::getInstance()->getSystem(System::Type::MotionController).get());
            motionControllerSystem->setActive(false);
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
        MotionControllerSystem* motionControllerSystem = static_cast<MotionControllerSystem*>(Engine::getInstance()->getSystem(System::Type::MotionController).get());
        motionControllerSystem->setActive(true);
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
    std::string path = App::getAbsolutePath() +
            App::getPathSeparator() + "Screenshot" + App::getPathSeparator() +
            std::to_string(now->tm_year + 1900) + "-" +
            std::to_string(now->tm_mon + 1) + "-" +
            std::to_string(now->tm_mday) + "_" +
            std::to_string(now->tm_hour) + "-" +
            std::to_string(now->tm_min) + "-" +
            std::to_string(now->tm_sec) + ".png";

    int width = App::getInstance()->getWidth();
    int height = App::getInstance()->getHeight();

    unsigned char* image = new unsigned char[width * height * 4];
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Vertically flip
    for (unsigned y = 0; y < height / 2; y++) {
        unsigned swapY = height - y - 1;
        for(unsigned x = 0; x < width; x++) {
            unsigned offset = 4 * (x + y * width);
            unsigned swapOffset = 4 * (x + swapY * width);

            unsigned char temp = image[offset + 0];
            image[offset + 0] = image[swapOffset + 0];
            image[swapOffset + 0] = temp;

            temp = image[offset + 1];
            image[offset + 1] = image[swapOffset + 1];
            image[swapOffset + 1] = temp;

            temp = image[offset + 2];
            image[offset + 2] = image[swapOffset + 2];
            image[swapOffset + 2] = temp;

            temp = image[offset + 3];
            image[offset + 3] = image[swapOffset + 3];
            image[swapOffset + 3] = temp;
        }
    }

    lodepng::encode(path, image, width, height);

    delete[] image;

    std::string message = "Screenshot saved to " + path;
    Toast::getInstance()->showToast(message);
}
