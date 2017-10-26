#include "View.h"
#include "Scene/Scene.h"
#include "Graphics/Vulkan/Semaphore.h"
#include "Graphics/Vulkan/Context.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"

View::View() {
    scene = std::make_shared<Scene>();
    device = Vulkan::Context::get()->getGraphicsDevice();

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
