#include "PauseDialog.h"
#include "../../Graphics/Vulkan/Queue/SubmitQueue.h"

PauseDialog::PauseDialog() {

}

void PauseDialog::init() {

}

void PauseDialog::draw(float dt) {
    queue->submit();
}

void PauseDialog::update(float dt) {

}

void PauseDialog::writeCommands(Vulkan::CommandBuffer* commandBuffer) {

}

void PauseDialog::buildCommandBuffers() {

}
