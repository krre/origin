#include "Viewport.h"

#include "../Event/Event.h"
#include <SDL_opengl.h>

Viewport::Viewport() {
    Event::getInstance()->render.connectMember(&Viewport::render, this);
    Event::getInstance()->update.connectMember(&Viewport::update, this, placeholders::_1);
    camera = shared_ptr<Camera>(new Camera());
}

void Viewport::update(double dt) {
//    print("update: " << dt);
}

void Viewport::render() {
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Node* rootNode = scene->getRoot();
    rootNode->draw();
}
