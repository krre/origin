#include "View.h"
#include "Scene/Scene.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"
#include "Graphics/Vulkan/Semaphore.h"
#include "Graphics/Vulkan/Context.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"
#include "Graphics/Vulkan/Surface/Swapchain.h"
#include "Graphics/Vulkan/Command/CommandBuffers.h"

View::View() {
    scene = std::make_shared<Scene>();
    device = Vulkan::Context::get()->getGraphicsDevice();

    commandBuffers = std::make_shared<Vulkan::CommandBuffers>(device, Vulkan::Context::get()->getGraphicsCommandPool());
    commandBuffers->allocate(Application::get()->getWindow()->getSwapchain()->getCount());

    renderFinishedSemaphore = std::make_unique<Vulkan::Semaphore>(device);
    renderFinishedSemaphore->create();

    submitQueue = std::make_unique<Vulkan::SubmitQueue>(device, Vulkan::Context::get()->getGraphicsFamily());
    submitQueue->create();
}

View::~View() {

}

void View::update(float dt) {

}

void View::draw(float dt) {

}

void View::render() {
    submitQueue->submit();
}

void View::resize(uint32_t width, uint32_t height) {

}
