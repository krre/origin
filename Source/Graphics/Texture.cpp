#include "Texture.h"
#include <lodepng/lodepng.h>

Texture::Texture(const std::string& path) {
    lodepng::decode(data, width, height, path);
}
