#include "Viewport.h"
#include "../Event/Event.h"
#include <SDL_opengl.h>
#include <algorithm>

Viewport::Viewport() {
    currentCamera = std::make_shared<Camera>();
}

void Viewport::update(double dt) {

}

void Viewport::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Node* rootNode = scene->getRoot();
    rootNode->draw();
}

void Viewport::setBackgroundColor(const glm::vec4& backgroundColor) {
    this->backgroundColor = backgroundColor;
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

void Viewport::setRectangle(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void Viewport::addCamera(std::shared_ptr<Camera> camera) {
    cameras.push_back(camera);
}

void Viewport::removeCamera(std::shared_ptr<Camera> camera) {
    cameras.erase(std::remove(cameras.begin(), cameras.end(), camera), cameras.end());
}

void Viewport::clearCameras() {
    cameras.clear();
}

void Viewport::setCurrentCamera(std::shared_ptr<Camera> currentCamera) {
    this->currentCamera = currentCamera;
}
