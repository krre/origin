#include "Viewport.h"

#include "../Event/Event.h"
#include <SDL_opengl.h>

extern Event* event;

Viewport::Viewport() {
    ::event->render.connectMember(&Viewport::render, this);
    ::event->update.connectMember(&Viewport::update, this, std::placeholders::_1);
    camera = shared_ptr<Camera>(new Camera());
}

void Viewport::update(double dt) {
//    print("update: " << dt);
}

void Viewport::render() {
    glClearColor(0.25, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Node* rootNode = scene->getRoot();
    rootNode->draw();
}
