#include "DebugHUD.h"
#include "base/Game.h"
#include "ui/Label.h"
#include "graphics/render/RenderManager.h"
#include "vulkan/api/device/Device.h"
#include "vulkan/api/device/PhysicalDevice.h"
#include "vulkan/api/Instance.h"
#include <SDL.h>

DebugHUD::DebugHUD(Control* parent) : Control(parent) {
    setVisible(false);

    label = new Label(this);
    label->move(5, 5);
    int apiVersionNumber = RenderManager::get()->graphicsDevice()->physicalDevice()->properties().apiVersion;
    vulkanApiVersion = RenderManager::get()->instance()->apiToString((apiVersionNumber));
}

DebugHUD::~DebugHUD() {

}

void DebugHUD::updateImpl(float dt) {
    accumTime += dt;
    counter++;
    if (accumTime >= 0.5) {
        // Average fps for 0.5 sec (on resize may be > 60, so clamp to 60)
        fps = int(std::round(counter / accumTime));
        accumTime = 0;
        counter = 0;
    }

    std::string text =
        std::string(Game::Name) + " " + std::string(Game::Version) + " " + std::string(Game::Status) + "\n" +
        std::to_string(fps) + " fps\n"
        "Video driver: " + RenderManager::get()->graphicsDevice()->physicalDevice()->properties().deviceName + "\n"
        "Vulkan API: " + vulkanApiVersion + "\n"
        "CPU count: " + std::to_string(SDL_GetCPUCount()) + "\n"
        "System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB";

//    if (Game::get()->getWorldScene()) {
//        Entity* character = EntityManager::get()->getEntity(Game::get()->getWorldScene()->getCharacterId()).get();
//        TransformComponent* tc = character->getTransform();
//        std::string pos = "\n"
//        "Position X: " + std::to_string(tc->position.x) + "\n"
//        "Position Y: " + std::to_string(tc->position.y) + "\n"
//        "Position Z: " + std::to_string(tc->position.z);

//        text += pos;
//    }

    label->setText(text);
}
