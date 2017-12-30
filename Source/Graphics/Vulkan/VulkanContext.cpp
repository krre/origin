#include "VulkanContext.h"
#include "VulkanRenderWindow.h"

VulkanContext::VulkanContext() {

}

VulkanContext::~VulkanContext() {

}

RenderWindow* VulkanContext::createRenderWindow() {
    return new VulkanRenderWindow;
}
