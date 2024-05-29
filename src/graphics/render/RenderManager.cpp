#include "RenderManager.h"
#include "base/Game.h"
#include "base/Window.h"
#include "graphics/Color.h"
#include "core/Utils.h"
#include "vulkan/api/command/CommandBuffer.h"
#include "vulkan/api/Framebuffer.h"
#include "vulkan/api/RenderPass.h"
#include "Renderer.h"
#include "ui/Overlay.h"
#include "ui/Toast.h"
#include <lodepng/lodepng.h>

RenderManager::RenderManager(void* platformHandle, void* platformWindow, Object* parent) :
        Vulkan::Renderer(platformHandle, platformWindow),
        SingleObject(parent) {
}

RenderManager::~RenderManager() {

}

void RenderManager::addRenderer(::Renderer* renderer) {
    renderers.push_back(renderer);
}

void RenderManager::draw() {
    for (::Renderer* renderer : renderers) {
        if (renderer->getActive()) {
            renderer->draw();
        }
    }
}

void RenderManager::saveScreenshot() {
    std::string directoryPath = Game::getCurrentDirectory() + Core::Utils::getPathSeparator() + "Screenshot";

    if (!std::filesystem::exists(directoryPath)) {
        std::filesystem::create_directory(directoryPath);
    }

    time_t t = std::time(0); // Get time now
    struct tm* now = std::localtime(&t);
    std::string filename =
            std::to_string(now->tm_year + 1900) + "-" +
            Core::Utils::zeroFill(std::to_string(now->tm_mon + 1)) + "-" +
            Core::Utils::zeroFill(std::to_string(now->tm_mday)) + "_" +
            Core::Utils::zeroFill(std::to_string(now->tm_hour)) + "-" +
            Core::Utils::zeroFill(std::to_string(now->tm_min)) + "-" +
            Core::Utils::zeroFill(std::to_string(now->tm_sec)) + ".png";
    std::string filePath = directoryPath + Core::Utils::getPathSeparator() + filename;

    std::vector<unsigned char> buffer = readFramebuffer();
    lodepng::encode(filePath, buffer.data(), Window::get()->getWidth(), Window::get()->getHeight());

    std::string message = "Screenshot saved to " + filename;
    Overlay::get()->getToast()->show(message);
}

void RenderManager::init() {
}

void RenderManager::preRender() {
    if (currentScreen != Window::get()->getCurrentScreen()) {
        currentScreen = Window::get()->getCurrentScreen();
        markDirty();
    }
}

void RenderManager::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    VkExtent2D extent = { framebuffer->getWidth(), framebuffer->getHeight() };

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    commandBuffer->addViewport(viewport);
    commandBuffer->setViewport(0);

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    commandBuffer->addScissor(scissor);
    commandBuffer->setScissor(0);

    Vulkan::RenderPassBegin renderPassBegin(getRenderPass()->getHandle());
    renderPassBegin.setFrameBuffer(framebuffer->getHandle());
    renderPassBegin.setRenderArea({ 0, 0, framebuffer->getWidth(), framebuffer->getHeight() });
    const Color& color = Window::get()->getColor();
    renderPassBegin.addClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });
    VkClearValue depthColor = {};
    depthColor.depthStencil.depth = 1.0f;
    depthColor.depthStencil.stencil = 0.0f;
    renderPassBegin.addClearValue(depthColor);

    commandBuffer->beginRenderPass(renderPassBegin.getInfo());

    for (::Renderer* renderer : renderers) {
        if (renderer->getActive()) {
            renderer->writeCommandBuffer(commandBuffer, framebuffer);
        }
    }

    commandBuffer->endRenderPass();
}