#include "RenderManager.h"
#include "Base/Game.h"
#include "Base/Window.h"
#include "Screen/Screen.h"
#include "Core/Utils.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Surface/Surface.h"
#include "Resource/RenderPass/RenderPassResource.h"
#include "Resource/RenderPass/RenderPassUI.h"
#include "Resource/RenderPass/RenderPassVoxel.h"
#include "UIRenderer.h"
#include "SceneRenderer.h"
#include "UI/Overlay.h"
#include "UI/Toast.h"
#include <lodepng/lodepng.h>
#include <experimental/filesystem>

namespace Origin {

RenderManager::RenderManager(void* platformHandle, void* platformWindow, Object* parent) :
        Vulkan::Renderer(platformHandle, platformWindow),
        Object(parent) {
    window = Game::getWindow();
}

RenderManager::~RenderManager() {

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
    lodepng::encode(filePath, buffer.data(), window->getWidth(), window->getHeight());

    std::string message = "Screenshot saved to " + filename;
    Game::getOverlay()->getToast()->show(message);
}

void RenderManager::init() {
    uiRenderer = new UIRenderer(this);
    renderPassResources.push_back(uiRenderer->getRenderPassUI());

    sceneRenderer = new SceneRenderer(this);
    renderPassResources.push_back(sceneRenderer->getRenderPassVoxel());
}

void RenderManager::preRender() {
    if (currentScreen != window->getCurrentScreen()) {
        currentScreen = window->getCurrentScreen();
        updateCommandBuffers();
    }
}

void RenderManager::writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
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

    for (const auto renderPassResoure : renderPassResources) {
        renderPassResoure->write(commandBuffer, framebuffer);
    }
}

} // Origin
