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

void Texture::attachBuffer(GLenum internalFormat, GLuint buffer) {
    glTexBuffer(type, internalFormat, buffer);
}
