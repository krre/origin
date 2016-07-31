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
#include "../GameState/GameStateManager.h"
#include <SDL_keycode.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <ctime>
#include <lodepng/lodepng.h>

Game::Game() {
    create();
}

void Game::create() {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    TransformSystem* transformSystem = static_cast<TransformSystem*>(Engine::getInstance()->getSystem(SystemType::Transform).get());

    // Avatar
    auto avatar = EntityBuilder::avatar();
    Engine::getInstance()->addEntity(avatar);

    std::shared_ptr<Entity> avatarCamera = EntityBuilder::camera();
    App::getInstance()->getViewport()->setCurrentCamera(avatarCamera);
    transformSystem->translate(avatarCamera.get(), glm::vec3(0.0f, 0.1f, 0.0f));
    transformSystem->setPitch(avatarCamera.get(), -15.0);
    NodeSystem* nodeSystem = static_cast<NodeSystem*>(Engine::getInstance()->getSystem(SystemType::Node).get());
    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());

    MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::getInstance()->getSystem(SystemType::MovementController).get());
    movementControllerSystem->setMoveEntity(avatarCamera.get());
    movementControllerSystem->setRotateEntity(avatarCamera.get());

    Engine::getInstance()->addEntity(avatarCamera);

    // Plane
    std::shared_ptr<Entity> plane = EntityBuilder::plane();
    transformSystem->scale(plane.get(), glm::vec3(5.0, 1.0, 5.0));
    MaterialComponent* materialPlane = static_cast<MaterialComponent*>(plane->components[ComponentType::Material].get());
    materialPlane->color = glm::vec3(0.52, 0.35f, 0.35f);
    Engine::getInstance()->addEntity(plane);

    // Cube1
    std::shared_ptr<Entity> cube1 = EntityBuilder::cube();
    transformSystem->scale(cube1.get(), glm::vec3(0.2, 0.2, 0.2));
    transformSystem->translate(cube1.get(), glm::vec3(0.2, 0.21, -0.5));
    MaterialComponent* materialCube1 = static_cast<MaterialComponent*>(cube1->components[ComponentType::Material].get());
    materialCube1->color = glm::vec3(0.8, 0.1f, 0.1f);
    Engine::getInstance()->addEntity(cube1);

    // Cube2
    std::shared_ptr<Entity> cube2 = EntityBuilder::cube();
    transformSystem->scale(cube2.get(), glm::vec3(0.1, 0.3, 0.1));
    transformSystem->translate(cube2.get(), glm::vec3(-0.2, 0.25, 0.25));
    MaterialComponent* materialCube2 = static_cast<MaterialComponent*>(cube2->components[ComponentType::Material].get());
    materialCube2->color = glm::vec3(0.1, 0.5f, 0.9f);
    Engine::getInstance()->addEntity(cube2);

    // Light
    std::shared_ptr<Entity> light = EntityBuilder::light();
    transformSystem->translate(light.get(), glm::vec3(1.0, 1.0, 1.0));
    Engine::getInstance()->addEntity(light);

    App::getInstance()->getViewport()->setBackgroundColor(glm::vec4(0.77, 0.83, 0.83, 1.0));

    Event::getInstance()->keyPressed.connect<Game, &Game::onKeyPressed>(this);

    GameStateManager::getInstance()->setState(GameState::PLAY);
}

void Game::load() {

}

void Game::save() {

}

void Game::onKeyPressed(const SDL_KeyboardEvent& event) {
    GameState::Type gameState = GameStateManager::getInstance()->getStateType();
    switch (event.keysym.sym) {
    case SDLK_ESCAPE:
        if (Input::getInstance()->isKeyAccepted) break;
        if (gameState == GameState::PLAY) {
            GameStateManager::getInstance()->pushState(GameState::PAUSE);
        } else if (gameState == GameState::CONSOLE) {
            MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::getInstance()->getSystem(SystemType::MovementController).get());
            movementControllerSystem->setActive(true);
            Console::getInstance()->setVisible(false);
            GameStateManager::getInstance()->popState();
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
        if (gameState == GameState::PLAY) {
            MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::getInstance()->getSystem(SystemType::MovementController).get());
            movementControllerSystem->setActive(false);
            Console::getInstance()->setVisible(true);
            GameStateManager::getInstance()->pushState(GameState::CONSOLE);
        }
        break;

    default:
        break;
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
            zeroFill(std::to_string(now->tm_mon + 1)) + "-" +
            zeroFill(std::to_string(now->tm_mday)) + "_" +
            zeroFill(std::to_string(now->tm_hour)) + "-" +
            zeroFill(std::to_string(now->tm_min)) + "-" +
            zeroFill(std::to_string(now->tm_sec)) + ".png";

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

std::string Game::zeroFill(std::string number) {
    return (number.size() == 1 ? "0" : "") + number;
}
