#include "Manager.h"
#include "../../Core/App.h"
#include "../../Event/Event.h"
#include "../../Scene/SceneManager.h"
#include "Swapchain.h"

using namespace Vulkan;

Manager::~Manager() {
    Instance::get()->release();
}

void Manager::init() {
    new Instance();
    Instance* instance = Instance::get();
    instance->create();

    device = instance->getDefaultDevice();

    Event::get()->windowResize.connect<Manager, &Manager::onWindowResize>(this);
}

void Manager::onWindowResize(int width, int height) {
    if (App::get()->getIsRunning()) {
        device->waitIdle();
        Instance::get()->getSurface()->getSwapchain()->rebuild();
        Instance::get()->getCommandPool()->reset();
        SceneManager::get()->rebuild();
    }
}
