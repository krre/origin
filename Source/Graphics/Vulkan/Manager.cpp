#include "Manager.h"
#include "../../Core/App.h"
#include "../../Event/Event.h"
#include "../../Scene/SceneManager.h"

using namespace Vulkan;

Manager::~Manager() {
    swapchain.reset();
    renderPass.reset();
    Instance::get()->release();
}

void Manager::init() {
    new Instance();
    Instance* instance = Instance::get();
    instance->create();

    device = instance->getDefaultDevice();

    renderPass = std::make_shared<RenderPass>(device);
    renderPass->setColorFormat(instance->getSurface()->getFormats().at(0).format);
    renderPass->create();

    swapchain = std::make_shared<Swapchain>(instance->getSurface());
    swapchain->create();

    Event::get()->windowResize.connect<Manager, &Manager::onWindowResize>(this);
}

void Manager::onWindowResize(int width, int height) {
    if (App::get()->getIsRunning()) {
        device->waitIdle();
        swapchain->rebuild();
        Instance::get()->getCommandPool()->reset();
        SceneManager::get()->rebuild();
    }
}
