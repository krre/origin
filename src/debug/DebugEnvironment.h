#pragma once
#include <core/SingleObject.h>
#include <json/json.hpp>
#include <vulkan/vulkan.h>

using json = nlohmann::json;

class DebugEnvironment : public Core::SingleObject<DebugEnvironment> {

public:
    DebugEnvironment(Object* parent = nullptr);
    static bool getEnable() { return get()->enable; }
    static void setDebugScreen();
    static json& getSettings() { return get()->settings; }
    static int getVulkanDevice() { return get()->settings["vulkan"]["device"]; }
    static VkDebugReportFlagsEXT getVulkanDebugReportFlags();

private:
    void loadValues();
    bool enable = false;
    json settings;
};
