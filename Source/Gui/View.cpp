#include "View.h"
#include "Scene/Scene.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"
#include "Graphics/Vulkan/VulkanRenderContext.h"

namespace Origin {

View::View() {
    device = vkCtx->getGraphicsDevice();
}

View::~View() {

}

void View::update(float dt) {

}

void View::render() {

}

const std::vector<View*> View::getInnerViews() {
    innerViews.clear();
    innerViews.push_back(this);
    // TODO: Make recursive finding inner views from scene

    return innerViews;
}

} // Origin
