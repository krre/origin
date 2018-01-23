#include "RenderEngine.h"
#include "Core/Defines.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Screen.h"
#include "Core/Utils.h"
#include "Renderer2D.h"
#include "Renderer3D.h"
#include "Gui/Control.h"
#include "Gui/Batch2D.h"
#include "Debug/DebugEnvironment.h"
#include "Graphics/Render/RenderEngine.h"
#include "VulkanRenderer/API/Command/CommandBuffer.h"
#include "VulkanRenderer/API/Framebuffer.h"
#include "VulkanRenderer/API/RenderPass.h"
#include <lodepng/lodepng.h>
#include <SDL_syswm.h>

namespace Origin {

RenderEngine::RenderEngine(WindowSettings windowSettings) : Vulkan::Renderer(windowSettings) {
    window = Application::get()->getWindow();
}

RenderEngine::~RenderEngine() {

}

void RenderEngine::createShaderPrograms() {
//    shaderPrograms[ShaderProgram::ProgamType::Base] = RenderContext::get()->createShaderProgram("Base");
//    shaderPrograms[ShaderProgram::ProgamType::Sdf] = RenderContext::get()->createShaderProgram("Sdf");
//    shaderPrograms[ShaderProgram::ProgamType::Voxel] = RenderContext::get()->createShaderProgram("Voxel");
}

void RenderEngine::createRenderStates() {
//    // Shape2D
//    std::shared_ptr<RenderState> shape2DRS = RenderContext::get()->createRenderState();
//    shape2DRS->setShaderProgram(shaderPrograms[ShaderProgram::ProgamType::Base].get());
//    shape2DRS->setBlendEnable(true);
//    shape2DRS->create();
//    renderStates[RenderState::Type::Shape2D] = shape2DRS;

//    // Freetype text
//    std::shared_ptr<RenderState> freeTypeTextRS = RenderContext::get()->createRenderState();
//    shape2DRS->setBlendEnable(true);
//    shape2DRS->create();
//    renderStates[RenderState::Type::FreeTypeText] = freeTypeTextRS;

//    // SDF text
//    std::shared_ptr<RenderState> sdfTextRS = RenderContext::get()->createRenderState();
//    sdfTextRS->setShaderProgram(shaderPrograms[ShaderProgram::ProgamType::Sdf].get());
//    shape2DRS->setBlendEnable(true);
//    shape2DRS->create();
//    renderStates[RenderState::Type::SdfText] = sdfTextRS;

//    // Voxel
//    std::shared_ptr<RenderState> voxelRS = RenderContext::get()->createRenderState();
//    voxelRS->setShaderProgram(shaderPrograms[ShaderProgram::ProgamType::Voxel].get());
//    voxelRS->create();
//    renderStates[RenderState::Type::Voxel] = voxelRS;
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

void RenderEngine::prepare() {
    renderer2d->prepare(window->getScreen()->getRootControl());
    renderer2d->render();

    for (auto view3d : renderer2d->getRenderViews()) {
        renderer3d->render(view3d);
    }
}

void RenderEngine::init() {
    renderer2d = std::make_unique<Renderer2D>();
    renderer3d = std::make_unique<Renderer3D>();

    createShaderPrograms();
    createRenderStates();
}

void RenderEngine::writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    const Color& color = window->getColor();
    getRenderPass()->setClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });
    VkRenderPassBeginInfo* beginInfo = getRenderPass()->getBeginInfo();
    beginInfo->framebuffer = framebuffer->getHandle();

    VkExtent2D extent = { window->getWidth(), window->getHeight() };
    beginInfo->renderArea.extent = extent;

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    commandBuffer->begin();

    commandBuffer->beginRenderPass(beginInfo);

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

    commandBuffer->end();
}

} // Origin
