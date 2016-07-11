#include "Viewport.h"

#include "../Event/Event.h"
#include <SDL_opengl.h>

Viewport::Viewport() {
    camera = std::shared_ptr<Camera>(new Camera());
}

void Viewport::update(double dt) {
//    print("update: " << dt);
}

void Viewport::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Node* rootNode = scene->getRoot();
    rootNode->draw();
}

void Viewport::setBackgroundColor(const glm::vec4& backgroundColor) {
    this->backgroundColor = backgroundColor;
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

void Viewport::setRectangle(glm::vec4& rectangle) {
    this->rectangle = rectangle;
}
