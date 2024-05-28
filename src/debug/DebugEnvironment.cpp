#include "DebugEnvironment.h"
#include "base/Game.h"
#include "base/Defines.h"
#include "core/Utils.h"
#include "screen/MenuScreen.h"
#include "screen/SettingsScreen.h"
#include "screen/GameScreen.h"
#include "screen/NewWorldScreen.h"
#include "screen/LoadWorldScreen.h"
#include "screen/WaitScreen.h"
#include "base/Window.h"

DebugEnvironment::DebugEnvironment(Object* parent) : SingleObject(parent) {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

void DebugEnvironment::setDebugScreen() {
    uint8_t s = get()->settings["general"]["screen"];
    json j = get()->settings["general"]["save"];
    std::string worldName;
    if (j.is_string()) {
        worldName = j.get<std::string>();
    }
    Screen::Name screen = static_cast<Screen::Name>(s);
    switch (screen) {
        case Screen::Name::Menu:
            Window::get()->setScreen(std::make_shared<MenuScreen>());
            break;
        case Screen::Name::Settings:
            Window::get()->setScreen(std::make_shared<SettingsScreen>());
            break;
        case Screen::Name::Game:
            Window::get()->setScreen(std::make_shared<GameScreen>(worldName));
            break;
        case Screen::Name::NewGame:
            Window::get()->setScreen(std::make_shared<NewWorldScreen>());
            break;
        case Screen::Name::LoadGame:
            Window::get()->setScreen(std::make_shared<LoadWorldScreen>());
            break;
        case Screen::Name::Wait:
            Window::get()->setScreen(std::make_shared<WaitScreen>());
            break;
        default:
            assert(0 && "Screen not found");
    }
}

VkDebugReportFlagsEXT DebugEnvironment::getVulkanDebugReportFlags() {
    json debugReport = get()->settings["vulkan"]["debugReport"];
    VkDebugReportFlagsEXT flags = 0;

    if (debugReport["information"]) {
        flags |= VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
    }

    if (debugReport["warning"]) {
        flags |= VK_DEBUG_REPORT_WARNING_BIT_EXT;
    }

    if (debugReport["performance"]) {
        flags |= VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
    }

    if (debugReport["error"]) {
        flags |= VK_DEBUG_REPORT_ERROR_BIT_EXT;
    }

    if (debugReport["debug"]) {
        flags |= VK_DEBUG_REPORT_DEBUG_BIT_EXT;
    }

    return flags;
}

void DebugEnvironment::loadValues() {
    std::string filePath = Game::getCurrentDirectory() + "/debug.json";
    try {
        std::string text = Core::Utils::readTextFile(filePath);
        settings = json::parse(text);
        enable = settings["general"]["enable"];
    } catch (const std::exception& ex) {
        PRINT(ex.what())
    };
}
