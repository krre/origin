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
    TransformSystem* transformSystem = static_cast<TransformSystem*>(Engine::get()->getSystem(SystemType::Transform).get());
    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(Engine::get()->getSystem(SystemType::Octree).get());
    PhisicsSystem* phisicsSystem = static_cast<PhisicsSystem*>(Engine::get()->getSystem(SystemType::Phisics).get());

    // Free camera
    std::shared_ptr<Entity> freeCamera = EntityBuilder::freeCamera();
    transformSystem->lookAt(freeCamera.get(), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    transformSystem->translate(freeCamera.get(), glm::vec3(2.0f, 1.0f, 3.0f));
    App::get()->getViewport()->setCurrentCamera(freeCamera);
    Engine::get()->addEntity(freeCamera);

    // Avatar
    auto avatar = EntityBuilder::avatar();
    Engine::get()->addEntity(avatar);

    std::shared_ptr<Entity> avatarCamera = EntityBuilder::camera();
    App::get()->getViewport()->setCurrentCamera(avatarCamera);
    transformSystem->translate(avatarCamera.get(), glm::vec3(0.0f, 0.0f, 2.0f));
//    transformSystem->setPitch(avatarCamera.get(), -15.0);
//    NodeSystem* nodeSystem = static_cast<NodeSystem*>(Engine::get()->getSystem(SystemType::Node).get());
//    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());
    characterId = avatarCamera->getId();

    std::shared_ptr<PhisicsComponent> phisicsComponent = std::make_shared<PhisicsComponent>();
    phisicsComponent->mass = 1.0;
    phisicsComponent->collisionShape.reset(new btCapsuleShape(0.5, 1.75));
    Engine::get()->addComponent(avatarCamera.get(), phisicsComponent);
    phisicsSystem->createMotionState(avatarCamera.get());
    phisicsSystem->createRigidBody(avatarCamera.get());
    phisicsComponent->rigidBody->setAngularFactor(btVector3(0, 0, 0));
    phisicsSystem->addRigidBody(avatarCamera.get());

    Engine::get()->addEntity(avatarCamera);

    octreeSystem->getGpuMemoryManager()->beginBatch();

    // Ground
    std::shared_ptr<Entity> ground = EntityBuilder::geometry();
    transformSystem->setScale(ground.get(), 5);
    transformSystem->setPosition(ground.get(), glm::vec3(0.0, 1.0, 0.0));
    OctreeComponent* groundOctree = static_cast<OctreeComponent*>(ground->components[ComponentType::Octree].get());
    groundOctree->data = ResourceManager::get()->getResource<Octree>("GroundOctree")->data();
    Engine::get()->addEntity(ground);
    octreeSystem->getGpuMemoryManager()->addEntity(ground.get());

    // Trees
    std::shared_ptr<Entity> tree1 = EntityBuilder::geometry();
    transformSystem->setScale(tree1.get(), 1.2);
    transformSystem->setPosition(tree1.get(), glm::vec3(1.0, 0.15, 0.0));

    phisicsSystem->createCollisionShape(tree1.get());
    phisicsSystem->createMotionState(tree1.get());
    phisicsSystem->createRigidBody(tree1.get());
    phisicsSystem->addRigidBody(tree1.get());

    OctreeComponent* tree1Octree = static_cast<OctreeComponent*>(tree1->components[ComponentType::Octree].get());
    tree1Octree->data = ResourceManager::get()->getResource<Octree>("TreeOctree")->data();
    Engine::get()->addEntity(tree1);
    octreeSystem->getGpuMemoryManager()->addEntity(tree1.get());

    std::shared_ptr<Entity> tree2 = EntityBuilder::geometry();
    transformSystem->setScale(tree2.get(), 0.9);
    transformSystem->setPosition(tree2.get(), glm::vec3(-0.7, 0.15, 1.2));

    phisicsSystem->createCollisionShape(tree2.get());
    phisicsSystem->createMotionState(tree2.get());
    phisicsSystem->createRigidBody(tree2.get());
    phisicsSystem->addRigidBody(tree2.get());

    OctreeComponent* tree2Octree = static_cast<OctreeComponent*>(tree2->components[ComponentType::Octree].get());
    tree2Octree->data = ResourceManager::get()->getResource<Octree>("TreeOctree")->data();
    Engine::get()->addEntity(tree2);
    octreeSystem->getGpuMemoryManager()->addEntity(tree2.get());

    std::shared_ptr<Entity> tree3 = EntityBuilder::geometry();
    transformSystem->setScale(tree3.get(), 1.1);
    transformSystem->setPosition(tree3.get(), glm::vec3(-0.3, 0.15, -1.8));

    phisicsSystem->createCollisionShape(tree3.get());
    phisicsSystem->createMotionState(tree3.get());
    phisicsSystem->createRigidBody(tree3.get());
    phisicsSystem->addRigidBody(tree3.get());

    OctreeComponent* tree3Octree = static_cast<OctreeComponent*>(tree3->components[ComponentType::Octree].get());
    tree3Octree->data = ResourceManager::get()->getResource<Octree>("TreeOctree")->data();
    Engine::get()->addEntity(tree3);
    octreeSystem->getGpuMemoryManager()->addEntity(tree3.get());

    // Chamomiles
    std::shared_ptr<Entity> chamomile1 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile1.get(), 0.04);
    transformSystem->setPosition(chamomile1.get(), glm::vec3(0.2, -0.22, 0.2));
    OctreeComponent* chamomile1Octree = static_cast<OctreeComponent*>(chamomile1->components[ComponentType::Octree].get());
    chamomile1Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile1);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile1.get());

    std::shared_ptr<Entity> chamomile2 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile2.get(), 0.04);
    transformSystem->setPosition(chamomile2.get(), glm::vec3(-0.3, -0.22, 1.3));
    OctreeComponent* chamomile2Octree = static_cast<OctreeComponent*>(chamomile2->components[ComponentType::Octree].get());
    chamomile2Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile2);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile2.get());

    std::shared_ptr<Entity> chamomile3 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile3.get(), 0.04);
    transformSystem->setPosition(chamomile3.get(), glm::vec3(0.4, -0.22, 1.0));
    OctreeComponent* chamomile3Octree = static_cast<OctreeComponent*>(chamomile3->components[ComponentType::Octree].get());
    chamomile3Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile3);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile3.get());

    octreeSystem->getGpuMemoryManager()->endBatch();
    octreeSystem->getGpuMemoryManager()->updateRenderList();

    // Light
    std::shared_ptr<Entity> light = EntityBuilder::light();
    transformSystem->translate(light.get(), glm::vec3(1.5, 2.5, 1.0));
    Engine::get()->addEntity(light);

    Event::get()->keyPressed.connect<Game, &Game::onKeyPressed>(this);

    GameStateManager::get()->setState(GameState::MENU);
}

void Game::load() {

}

void Game::save() {

}

void Game::onKeyPressed(const SDL_KeyboardEvent& event) {
    GameState::Type gameState = GameStateManager::get()->getStateType();
    switch (event.keysym.sym) {
    case SDLK_ESCAPE:
        if (Input::get()->isKeyAccepted) break;
        if (gameState == GameState::PLAY) {
            GameStateManager::get()->pushState(GameState::PAUSE);
        } else if (gameState == GameState::CONSOLE) {
            MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::get()->getSystem(SystemType::MovementController).get());
            movementControllerSystem->setActive(true);
            Console::get()->setVisible(false);
            GameStateManager::get()->popState();
        }
        break;
#ifdef DEBUG_HUD_ENABLE
    case SDLK_F5:
        DebugHUD::get()->trigger();
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
            MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::get()->getSystem(SystemType::MovementController).get());
            movementControllerSystem->setActive(false);
            Console::get()->setVisible(true);
            GameStateManager::get()->pushState(GameState::CONSOLE);
        }
        break;
#endif
#ifdef DEVELOP_MODE
    case SDLK_KP_0:
        App::get()->getViewport()->switchCamera();
        break;
#endif
    default:
        break;
    }
}

void Game::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(App::get()->getWindow()) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(App::get()->getWindow(), isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
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

    int width = App::get()->getWidth();
    int height = App::get()->getHeight();

    unsigned char* image = new unsigned char[width * height * 4];
//    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

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
    Toast::get()->showToast(message);
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
