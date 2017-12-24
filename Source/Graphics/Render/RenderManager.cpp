#include "RenderManager.h"
#include "Core/Screen.h"
#include "UI/Control.h"
#include "UI/Batch2D.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Vulkan/Semaphore.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"
#include "Graphics/Vulkan/Context.h"

RenderManager::RenderManager() {
    device = Vulkan::Context::get()->getGraphicsDevice();
    submitQueue = std::make_unique<Vulkan::SubmitQueue>(device, Vulkan::Context::get()->getGraphicsFamily());
    submitQueue->create();
}

RenderManager::~RenderManager() {
    submitQueue->waitIdle();
}

void RenderManager::renderScreen(Screen* screen, Vulkan::Semaphore* waitSemaphore, Vulkan::Semaphore* signalSemaphore, uint32_t imageIndex) {
    if (screen->getRootControl() == nullptr) return;

    std::vector<std::unique_ptr<Batch2D>> batches;
    VertexBuffer vertexBuffer(1000000);
    IndexBuffer indexBuffer(1000000);

    screen->getRootControl()->getBatches(batches, &vertexBuffer, &indexBuffer);

    submitQueue->clearWaitSemaphores();
    submitQueue->addWaitSemaphore(waitSemaphore);

    submitQueue->clearCommandBuffers();
    submitQueue->addCommandBuffer(screen->getCommandBuffer(imageIndex),
                                  waitSemaphore, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, signalSemaphore);
    submitQueue->submit();
}
