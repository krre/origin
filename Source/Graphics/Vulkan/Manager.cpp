#include "Manager.h"

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
    shaderModule.release();
    swapchain.release();
    queue.release();
    surface.release();
    device.release();
    physicalDevices.release();
    debugCallback.release();
    instance.release();
}

bool Manager::init() {
    instance.reset(new Instance);
    if (!instance->isValid()) {
        resultDescription = std::string(initError) + instance->getResultDescription();
        return false;
    }

    debugCallback.reset(new DebugReportCallback(instance.get()));
    if (!debugCallback->isValid()) {
        resultDescription = std::string(initError) + debugCallback->getResultDescription();
        return false;
    }

    physicalDevices.reset(new PhysicalDevices(instance.get()));
    device.reset(new Device(physicalDevices.get()));
    if (!device->isValid()) {
        resultDescription = std::string(initError) + device->getResultDescription();
        return false;
    }

    surface.reset(new Surface(instance.get()));
    if (!surface->isValid()) {
        resultDescription = std::string(initError) + surface->getResultDescription();
        return false;
    }

    queue.reset(new Queue(device.get()));
    if (!queue->isValid()) {
        resultDescription = std::string(initError) + queue->getResultDescription();
        return false;
    }

    swapchain.reset(new Swapchain(device.get(), surface.get()));
    if (!swapchain->isValid()) {
        resultDescription = std::string(initError) + swapchain->getResultDescription();
        return false;
    }

//    shaderModule.reset(new ShaderModule(device.get()));
//    if (!shaderModule->isValid()) {
//        resultDescription = std::string(initError) + shaderModule->getResultDescription();
//        return false;
//    }

    return true;
}

void Manager::addShaderCode(size_t size, const uint32_t* code) {
    ShaderCode shaderCode { size, code };
    shaderCodes.push_back(shaderCode);
}
