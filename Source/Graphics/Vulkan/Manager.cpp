#include "Manager.h"
#include "../../Resource/ShaderResource.h"
#include "../../Resource/ResourceManager.h"

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
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

    pipelineLayout.reset(new PipelineLayout(device.get()));
    if (!pipelineLayout->isValid()) {
        resultDescription = std::string(initError) + pipelineLayout->getResultDescription();
        return false;
    }

    graphicsPipeline.reset(new Pipeline(PipelineType::Graphics, device.get()));
    ShaderResource* shaderResource;

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseVertShader");
    graphicsPipeline->addShaderCode(ShaderType::Vertex, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseFragShader");
    graphicsPipeline->addShaderCode(ShaderType::Fragment, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    graphicsPipeline->create();

    if (!graphicsPipeline->isValid()) {
        resultDescription = std::string(initError) + graphicsPipeline->getResultDescription();
        return false;
    }

    return true;
}

