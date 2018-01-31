#include "RenderEngine.h"
#include "Core/Defines.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Screen/Screen.h"
#include "Core/Utils.h"
#include "UI/Control.h"
#include "UI/UIBatch.h"
#include "Debug/DebugEnvironment.h"
#include "Graphics/Render/RenderEngine.h"
#include "VulkanRenderer/API/Command/CommandBuffer.h"
#include "VulkanRenderer/API/Framebuffer.h"
#include "VulkanRenderer/API/RenderPass.h"
#include "VulkanRenderer/API/Surface/Surface.h"
#include "Resource/RenderPass/RenderPassResource.h"
#include <lodepng/lodepng.h>
#include <SDL_syswm.h>

namespace Origin {

RenderEngine::RenderEngine(void* platformHandle, void* platformWindow) :
        Vulkan::Renderer(platformHandle, platformWindow) {
    window = Application::get()->getWindow();
}

RenderEngine::~RenderEngine() {

}

void RenderEngine::saveScreenshot() {
    std::string directoryPath = Application::getCurrentDirectory() + Utils::getPathSeparator() + "Screenshot";
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
//    Toast::get()->showToast(message);
    PRINT(message)
}

void RenderEngine::init() {

}

void RenderEngine::preRender() {
    if (currentScreen != window->getCurrentScreen()) {
        currentScreen = window->getCurrentScreen();
        updateCommandBuffers();
    }
}

void RenderEngine::writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    VkExtent2D extent = getSurface()->getCurrentExtent();
    const Color& color = window->getColor();

    Vulkan::RenderPassBegin renderPassBegin(getRenderPass()->getHandle());
    renderPassBegin.setFrameBuffer(framebuffer->getHandle());
    renderPassBegin.setRenderArea({ 0, 0, extent.width, extent.height });
    renderPassBegin.addClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    if (currentScreen) {
        for (const auto renderPassResoure : currentScreen->getRenderPassResources()) {
            renderPassResoure->write(commandBuffer);
        }
    }

    commandBuffer->beginRenderPass(renderPassBegin.get());

    //    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());

    commandBuffer->addViewport(viewport);
    commandBuffer->setViewport(0);

    commandBuffer->addScissor(scissor);
    commandBuffer->setScissor(0);

    //    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    //    commandBuffer->bindVertexBuffers();
    //    commandBuffer->bindIndexBuffer(indexBuffer->getHandle(), indexBuffer->getIndexType());

    //    for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
    //        commandBuffer->addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
    //    }
    //    commandBuffer->bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());
    //    commandBuffer->drawIndexed(MAX_CHAR_COUNT, 1, 0, 0, 0);

    commandBuffer->endRenderPass();
}

} // Origin
