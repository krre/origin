#include "Manager.h"

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
    shaderModules.clear();
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

    return true;
}

bool Manager::createSurface() {
    surface.reset(new Surface(instance.get()));
    if (!surface->isValid()) {
        resultDescription = std::string(initError) + surface->getResultDescription();
        return false;
    }

    surfaceFormat.reset(new SurfaceFormat(physicalDevices.get(), surface.get()));

    queue.reset(new Queue(device.get()));
    if (!queue->isValid()) {
        resultDescription = std::string(initError) + queue->getResultDescription();
        return false;
    }

    swapchain.reset(new Swapchain(device.get(), surface.get(), surfaceFormat.get()));
    if (!swapchain->isValid()) {
        resultDescription = std::string(initError) + swapchain->getResultDescription();
        return false;
    }

    for (uint32_t i = 0; i < imageViews.size(); i++) {
        std::shared_ptr<ImageView> imageView(new ImageView(device.get(), surfaceFormat.get(), (*swapchain->getImages())[i]));
        if (!imageView->isValid()) {
            resultDescription = std::string(initError) + imageView->getResultDescription();
            return false;
        }
        imageViews.push_back(imageView);
    }

    renderPass.reset(new RenderPass(device.get(), surfaceFormat.get()));
    if (!renderPass->isValid()) {
        resultDescription = std::string(initError) + renderPass->getResultDescription();
        return false;
    }

    for (auto shaderCode : shaderCodes) {
        std::shared_ptr<ShaderModule> shaderModule(new ShaderModule(device.get(), shaderCode->size, shaderCode->code));
        if (!shaderModule->isValid()) {
            resultDescription = std::string(initError) + shaderModule->getResultDescription();
            return false;
        }
        shaderModules.push_back(shaderModule);

    }

    pipelineLayout.reset(new PipelineLayout(device.get()));
    if (!pipelineLayout->isValid()) {
        resultDescription = std::string(initError) + pipelineLayout->getResultDescription();
        return false;
    }

    return true;
}

void Manager::addShaderCode(size_t size, const uint32_t* code) {
    std::shared_ptr<ShaderCode> shaderCode(new ShaderCode { size, code });
    shaderCodes.push_back(shaderCode);
}
