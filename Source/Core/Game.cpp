#include "Game.h"
#include "App.h"
#include "Utils.h"
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
#include "../Resource/ResourceManager.h"
#include <SDL_keycode.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <ctime>
#include <lodepng/lodepng.h>
#include <Gagarin.h>
#include <experimental/filesystem>

Game::Game() {
#ifdef DEVELOP_MODE
    loadDevelopSettings();
#endif

    create();
}

void Game::create() {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    TransformSystem* transformSystem = static_cast<TransformSystem*>(Engine::getInstance()->getSystem(SystemType::Transform).get());
    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(Engine::getInstance()->getSystem(SystemType::Octree).get());
    RenderSystem* renderSystem = static_cast<RenderSystem*>(Engine::getInstance()->getSystem(SystemType::Render).get());

    // Free camera
    std::shared_ptr<Entity> freeCamera = EntityBuilder::freeCamera();
    transformSystem->lookAt(freeCamera.get(), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//    transformSystem->translate(freeCamera.get(), glm::vec3(2.0f, 0.0f, 0.0f));
    App::getInstance()->getViewport()->setCurrentCamera(freeCamera);
    Engine::getInstance()->addEntity(freeCamera);

    // Avatar
    auto avatar = EntityBuilder::avatar();
    Engine::getInstance()->addEntity(avatar);

    std::shared_ptr<Entity> avatarCamera = EntityBuilder::camera();
    App::getInstance()->getViewport()->setCurrentCamera(avatarCamera);
    transformSystem->translate(avatarCamera.get(), glm::vec3(0.0f, 0.0f, 2.0f));
//    transformSystem->setPitch(avatarCamera.get(), -15.0);
//    NodeSystem* nodeSystem = static_cast<NodeSystem*>(Engine::getInstance()->getSystem(SystemType::Node).get());
//    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());

    Engine::getInstance()->addEntity(avatarCamera);

    octreeSystem->getGpuMemoryManager()->beginBatch();

    // Ground
    std::shared_ptr<Entity> ground = EntityBuilder::geometry();
    transformSystem->setScale(ground.get(), 5);
    transformSystem->setPosition(ground.get(), glm::vec3(0.0, 1.0, 0.0));
    OctreeComponent* groundOctree = static_cast<OctreeComponent*>(ground->components[ComponentType::Octree].get());
    groundOctree->data = ResourceManager::getInstance()->getOctree("GroundOctree")->data();
    Engine::getInstance()->addEntity(ground);
    octreeSystem->getGpuMemoryManager()->addEntity(ground.get());

    // Trees
    std::shared_ptr<Entity> tree1 = EntityBuilder::geometry();
    transformSystem->setScale(tree1.get(), 0.5);
    transformSystem->setPosition(tree1.get(), glm::vec3(1.0, 0.3, 0.0));
    OctreeComponent* tree1Octree = static_cast<OctreeComponent*>(tree1->components[ComponentType::Octree].get());
    tree1Octree->data = ResourceManager::getInstance()->getOctree("TreeOctree")->data();
    Engine::getInstance()->addEntity(tree1);
    octreeSystem->getGpuMemoryManager()->addEntity(tree1.get());

    std::shared_ptr<Entity> tree2 = EntityBuilder::geometry();
    transformSystem->setScale(tree2.get(), 0.6);
    transformSystem->setPosition(tree2.get(), glm::vec3(-0.7, 0.3, 1.2));
    OctreeComponent* tree2Octree = static_cast<OctreeComponent*>(tree2->components[ComponentType::Octree].get());
    tree2Octree->data = ResourceManager::getInstance()->getOctree("TreeOctree")->data();
    Engine::getInstance()->addEntity(tree2);
    octreeSystem->getGpuMemoryManager()->addEntity(tree2.get());

    std::shared_ptr<Entity> tree3 = EntityBuilder::geometry();
    transformSystem->setScale(tree3.get(), 0.7);
    transformSystem->setPosition(tree3.get(), glm::vec3(-0.3, 0.3, -1.8));
    OctreeComponent* tree3Octree = static_cast<OctreeComponent*>(tree3->components[ComponentType::Octree].get());
    tree3Octree->data = ResourceManager::getInstance()->getOctree("TreeOctree")->data();
    Engine::getInstance()->addEntity(tree3);
    octreeSystem->getGpuMemoryManager()->addEntity(tree3.get());

    // Chamomiles
    std::shared_ptr<Entity> chamomile1 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile1.get(), 0.1);
    transformSystem->setPosition(chamomile1.get(), glm::vec3(0.2, -0.2, 0.2));
    OctreeComponent* chamomile1Octree = static_cast<OctreeComponent*>(chamomile1->components[ComponentType::Octree].get());
    chamomile1Octree->data = ResourceManager::getInstance()->getOctree("ChamomileOctree")->data();
    Engine::getInstance()->addEntity(chamomile1);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile1.get());

    std::shared_ptr<Entity> chamomile2 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile2.get(), 0.1);
    transformSystem->setPosition(chamomile2.get(), glm::vec3(-0.3, -0.2, 1.3));
    OctreeComponent* chamomile2Octree = static_cast<OctreeComponent*>(chamomile2->components[ComponentType::Octree].get());
    chamomile2Octree->data = ResourceManager::getInstance()->getOctree("ChamomileOctree")->data();
    Engine::getInstance()->addEntity(chamomile2);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile2.get());

    std::shared_ptr<Entity> chamomile3 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile3.get(), 0.1);
    transformSystem->setPosition(chamomile3.get(), glm::vec3(0.4, -0.2, 1.0));
    OctreeComponent* chamomile3Octree = static_cast<OctreeComponent*>(chamomile3->components[ComponentType::Octree].get());
    chamomile3Octree->data = ResourceManager::getInstance()->getOctree("ChamomileOctree")->data();
    Engine::getInstance()->addEntity(chamomile3);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile3.get());

    octreeSystem->getGpuMemoryManager()->endBatch();

    // Light
    std::shared_ptr<Entity> light = EntityBuilder::light();
    transformSystem->translate(light.get(), glm::vec3(1.5, 2.5, 1.0));
    Engine::getInstance()->addEntity(light);

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
#ifdef DEBUG_HUD_ENABLE
    case SDLK_F5:
        DebugHUD::getInstance()->trigger();
        break;
#endif
    case SDLK_F10:
        // TODO: Incorrect work
//        toggleFullScreen();
        break;

    case SDLK_F12:
        saveScreenshot();
        break;
#ifdef CONSOLE_ENABLE
    case SDLK_SLASH:
        if (gameState == GameState::PLAY) {
            MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::getInstance()->getSystem(SystemType::MovementController).get());
            movementControllerSystem->setActive(false);
            Console::getInstance()->setVisible(true);
            GameStateManager::getInstance()->pushState(GameState::CONSOLE);
        }
        break;
#endif
#ifdef DEVELOP_MODE
    case SDLK_KP_0:
        App::getInstance()->getViewport()->switchCamera();
        break;
#endif
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
    std::string directoryPath = App::getCurrentPath() + Utils::getPathSeparator() + "Screenshot";
    namespace fs = std::experimental::filesystem;
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    time_t t = std::time(0); // Get time now
    struct tm* now = std::localtime(&t);
    std::string filename =
            std::to_string(now->tm_year + 1900) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mon + 1)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mday)) + "_" +
            Utils::zeroFill(std::to_string(now->tm_hour)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_min)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_sec)) + ".png";
    std::string filePath = directoryPath + Utils::getPathSeparator() + filename;

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
            unsigned char temp;

            for (int channel = 0; channel <= 3; channel++ ) {
                temp = image[offset + channel];
                image[offset + channel] = image[swapOffset + channel];
                image[swapOffset + channel] = temp;
            }
        }
    }

    lodepng::encode(filePath, image, width, height);

    delete[] image;

    std::string message = "Screenshot saved to " + filename;
    Toast::getInstance()->showToast(message);
}

void Game::loadDevelopSettings() {
    std::string mainDebugPath = App::getCurrentPath() + "/Debug/main.debug";
    std::string mainDebugText = Utils::readTextFile(mainDebugPath);
    std::stringstream stream(mainDebugText);
    std::string line;

    while (std::getline(stream, line, '\n')) {
//        print(line)
    }
}
