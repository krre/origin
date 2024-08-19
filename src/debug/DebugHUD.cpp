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

    m_label = new Label(this);
    m_label->move(5, 5);
    int apiVersionNumber = RenderManager::get()->graphicsDevice()->physicalDevice()->properties().apiVersion;
    m_vulkanApiVersion = RenderManager::get()->instance()->apiToString((apiVersionNumber));
}

void DebugHUD::updateImpl(float dt) {
    m_accumTime += dt;
    m_counter++;
    if (m_accumTime >= 0.5) {
        // Average fps for 0.5 sec (on resize may be > 60, so clamp to 60)
        m_fps = int(std::round(m_counter / m_accumTime));
        m_accumTime = 0;
        m_counter = 0;
    }

    std::string text =
        std::string(Game::Name) + " " + std::string(Game::Version) + " " + std::string(Game::Status) + "\n" +
        std::to_string(m_fps) + " fps\n"
        "Video driver: " + RenderManager::get()->graphicsDevice()->physicalDevice()->properties().deviceName + "\n"
        "Vulkan API: " + m_vulkanApiVersion + "\n"
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

    m_label->setText(text);
}
