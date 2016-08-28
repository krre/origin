#include "Utils.h"

Utils::Utils() {

}

std::string Utils::zeroFill(const std::string& number) {
    return (number.size() == 1 ? "0" : "") + number;
}

std::string Utils::getPathSeparator() {
#ifdef _WIN32
    return "\\";
#else
    return "/";
#endif
}

uint32 Utils::rgbaToUint32(const glm::vec4& color) {
    return (((int(color.r * 255) & 0xff) << 24) + ((int(color.g * 255) & 0xff) << 16) + ((int(color.b * 255) & 0xff) << 8) + (int(color.a * 255) & 0xff));
}
