#include "Manager.h"

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
    swapchain.release();
    queue.release();
    surface.release();
    device.release();
    physicalDevices.release();
    instance.release();
}

bool Manager::init() {
    // Vulkan instance
    instance.reset(new Instance);
    if (!instance->isValid()) {
        resultDescription = std::string(initError) + instance->getResultDescription();
        return false;
    }

    // Vulkan device
    physicalDevices.reset(new PhysicalDevices(instance.get()));
    device.reset(new Device(physicalDevices.get()));
    if (!device->isValid()) {
        resultDescription = std::string(initError) + device->getResultDescription();
        return false;
    }

    // Vulkan surface
    surface.reset(new Surface(instance.get()));
    if (!surface->isValid()) {
        resultDescription = std::string(initError) + surface->getResultDescription();
        return false;
    }

    // Vulkan queue
    queue.reset(new Queue(device.get()));
    if (!queue->isValid()) {
        resultDescription = std::string(initError) + queue->getResultDescription();
        return false;
    }

    // Vulkan swapchain
    swapchain.reset(new Swapchain(device.get(), surface.get()));
    if (!swapchain->isValid()) {
        resultDescription = std::string(initError) + swapchain->getResultDescription();
        return false;
    }

    return true;
}
