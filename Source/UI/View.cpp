#include "View.h"
#include "Scene/Scene.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"
#include "Graphics/Vulkan/Context.h"

View::View() {
    scene = std::make_unique<Scene>();
    device = Vulkan::Context::get()->getGraphicsDevice();
}

View::~View() {

}

void View::update(float dt) {

}

void View::draw(float dt) {

}

void View::render() {

}

const std::vector<View*> View::getInnerViews() {
    innerViews.clear();
    innerViews.push_back(this);
    // TODO: Make recursive finding inner views from scene

    return innerViews;
}
