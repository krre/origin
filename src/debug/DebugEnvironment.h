#pragma once
#include <core/SingleObject.h>
#include <json/json.hpp>
#include <vulkan/vulkan.h>

using json = nlohmann::json;

class DebugEnvironment : public Core::SingleObject<DebugEnvironment> {
public:
    DebugEnvironment(Object* parent = nullptr);

    static bool enabled() { return get()->m_enabled; }
    static void setDebugScreen();
    static json& settings() { return get()->m_settings; }
    static int vulkanDevice() { return get()->m_settings["vulkan"]["device"]; }
    static VkDebugReportFlagsEXT vulkanDebugReportFlags();

private:
    void loadValues();
    bool m_enabled = false;
    json m_settings;
};
