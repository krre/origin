#include "RenderManager.h"
#include "Base/Game.h"
#include "Base/Window.h"
#include "Graphics/Color.h"
#include "Screen/Screen.h"
#include "Core/Utils.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Surface/Surface.h"
#include "Renderer.h"
#include "UI/Overlay.h"
#include "UI/Toast.h"
#include <lodepng/lodepng.h>
#include <experimental/filesystem>

namespace Origin {

RenderManager::RenderManager(void* platformHandle, void* platformWindow, Object* parent) :
        Vulkan::Renderer(platformHandle, platformWindow),
        SingleObject(parent) {
}

RenderManager::~RenderManager() {

}

void RenderManager::addRenderer(Origin::Renderer* renderer) {
    renderers.push_back(renderer);
}

void RenderManager::draw() {
    for (Origin::Renderer* renderer : renderers) {
        if (renderer->getActive()) {
            renderer->draw();
        }
    }
}

void RenderManager::saveScreenshot() {
    std::string directoryPath = Game::getCurrentDirectory() + Utils::getPathSeparator() + "Screenshot";
    namespace fs = std::experimental::filesystem;
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    time_t t = std::time(0); // Get time now
    struct tm* now = std::localtime(&t);
    std::string filename =
            std::to_string(now->tm_year + 1900) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mon + 1)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mday)) + "_" +
            Utils::zeroFill(std::to_string(now->tm_hour)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_min)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_sec)) + ".png";
    std::string filePath = directoryPath + Utils::getPathSeparator() + filename;

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
        updateCommandBuffers();
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

    for (Origin::Renderer* renderer : renderers) {
        if (renderer->getActive()) {
            renderer->writeCommandBuffer(commandBuffer, framebuffer);
        }
    }

    commandBuffer->endRenderPass();
}

} // Origin
