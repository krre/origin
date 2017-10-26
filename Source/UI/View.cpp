#include "View.h"
#include "Scene/Scene.h"

View::View() {
    scene = std::make_shared<Scene>();
}

View::~View() {

}

void View::update(float dt) {

}

void View::draw(float dt) {

}

void View::render(float dt) {

}

void View::resize(uint32_t width, uint32_t height) {

}
