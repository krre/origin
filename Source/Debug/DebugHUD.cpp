#include "DebugHUD.h"
#include "UI/Label.h"
#include "Base/Constants.h"
#include "Graphics/Render/RenderManager.h"
#include "Vulkan/API/Device/Device.h"
#include "Vulkan/API/Device/PhysicalDevice.h"
#include "Vulkan/API/Instance.h"
#include <SDL.h>

DebugHUD::DebugHUD(Control* parent) : Control(parent) {
    setVisible(false);

    label = new Label(this);
    label->move(5, 5);
    int apiVersionNumber = RenderManager::get()->getGraphicsDevice()->getPhysicalDevice()->getProperties().apiVersion;
    vulkanApiVersion = RenderManager::get()->getInstance()->apiToString((apiVersionNumber));
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
        std::string(Constants::App::NAME) + " " +
            std::string(Constants::App::VERSION) + " " +
            std::string(Constants::App::STATUS) + "\n" +

        std::to_string(fps) + " fps\n"
        "Video driver: " + RenderManager::get()->getGraphicsDevice()->getPhysicalDevice()->getProperties().deviceName + "\n"
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
