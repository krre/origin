#include "Renderer.h"
#include <SDL_opengl.h>

Renderer::Renderer() {

}

void Renderer::render() {
    glClearColor(0.25, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
