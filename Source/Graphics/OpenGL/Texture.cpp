#include "Texture.h"

Texture::Texture(GLenum type) : type(type) {
    glGenTextures(1, &id);
}

void Texture::bind() {
    glBindTexture(type, id);
}

void Texture::unbind() {
    glBindTexture(type, 0);
}
