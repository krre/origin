#include "Manager.h"
#include "../../Core/App.h"
#include "../../Event/Event.h"
#include "../../Scene/SceneManager.h"
#include <glm/glm.hpp>
#include <fstream>

using namespace Vulkan;

Manager::~Manager() {
    presentQueue.reset();
    imageAvailableSemaphore.reset();
    swapchain.reset();
    renderPass.reset();
    commandPool.reset();
    Instance::get()->release();
}

void Manager::init() {
    new Instance();
    Instance* instance = Instance::get();
    instance->create();

    device = instance->getDefaultDevice();

    commandPool = std::make_shared<CommandPool>(instance->getGraphicsFamily());
    commandPool->create();

    renderPass = std::make_shared<RenderPass>(device);
    renderPass->setColorFormat(instance->getSurface()->getFormats().at(0).format);
    renderPass->create();

    swapchain = std::make_shared<Swapchain>(instance->getSurface());
    swapchain->create();

    imageAvailableSemaphore = std::make_shared<Semaphore>(device);
    imageAvailableSemaphore->create();

    presentQueue = std::make_shared<PresentQueue>(instance->getGraphicsFamily());
    presentQueue->addSwapchain(swapchain->getHandle());

    Event::get()->windowResize.connect<Manager, &Manager::onWindowResize>(this);
}

void Manager::renderBegin() {
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, presentQueue->getImageIndex(swapchain->getIndex()));
}

void Manager::renderEnd() {
    presentQueue->present();
}

void Manager::onWindowResize(int width, int height) {
    if (App::get()->getIsRunning()) {
        device->waitIdle();
        swapchain->destroy();
        swapchain->create();
        presentQueue->clearSwapchain();
        presentQueue->addSwapchain(swapchain->getHandle());
        commandPool->reset();
        SceneManager::get()->rebuild();
    }
}
