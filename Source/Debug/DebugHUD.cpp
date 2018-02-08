#include "DebugHUD.h"
#include "UI/Label.h"
#include "Core/Defines.h"
#include "Core/Game.h"
#include "Graphics/Render/RenderManager.h"
#include "VulkanRenderer/API/Device/Device.h"
#include "VulkanRenderer/API/Device/PhysicalDevice.h"
#include "VulkanRenderer/API/Instance.h"
#include <SDL.h>

namespace Origin {

DebugHUD::DebugHUD(Control* parent) : Control(parent) {
    setVisible(false);

    displayLabel = new Label(this);
    displayLabel->move(5, 0);
    int apiVersionNumber = Game::getRenderManager()->getGraphicsDevice()->getPhysicalDevice()->getProperties().apiVersion;
    vulkanApiVersion = Game::getRenderManager()->getInstance()->apiToString((apiVersionNumber));
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
        std::string(APP_NAME) + " " + std::string(APP_VERSION_STR) + "\n" +
        std::to_string(fps) + " fps\n"
        "Video driver: " + Game::getRenderManager()->getGraphicsDevice()->getPhysicalDevice()->getProperties().deviceName + "\n"
        "Vulkan API: " + vulkanApiVersion + "\n"
        "CPU count: " + std::to_string(SDL_GetCPUCount()) + "\n"
        "System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB";

//    if (Game::get()->getWorldScene()) {
//        Entity* character = EntityManager::get()->getEntity(Game::get()->getWorldScene()->getCharacterId()).get();
//        TransformComponent* tc = static_cast<TransformComponent*>(character->components[ComponentType::Transform].get());
//        std::string pos = "\n"
//        "Position X: " + std::to_string(tc->position.x) + "\n"
//        "Position Y: " + std::to_string(tc->position.y) + "\n"
//        "Position Z: " + std::to_string(tc->position.z);

//        text += pos;
//    }

    displayLabel->setText(text);
}

} // Origin
