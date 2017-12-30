#include "VulkanContext.h"
#include "VulkanRenderWindow.h"

VulkanContext::VulkanContext() {

}

VulkanContext::~VulkanContext() {

}

RenderWindow* VulkanContext::createRenderWindowImpl() {
    return new VulkanRenderWindow;
}
