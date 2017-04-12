#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "RenderPass.h"
#include <string>
#include <vector>

namespace Vulkan {

class Manager : public Singleton<Manager> {

public:
    ~Manager();
    void init();

private:
    void onWindowResize(int width, int height);
    Device* device;
};

} // Vulkan
