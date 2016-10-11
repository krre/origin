#include "Utils.h"
#include <fstream>

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

uint32_t Utils::rgbaToUint32(const glm::vec4& color) {
    return (((int(color.r * 255) & 0xff) << 24) + ((int(color.g * 255) & 0xff) << 16) + ((int(color.b * 255) & 0xff) << 8) + (int(color.a * 255) & 0xff));
}

std::string Utils::readTextFile(const std::string& filePath) {
    std::ifstream in(filePath);
    if (in.is_open()) {
        std::string text((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
        return text;
    } else {
        error("Failed open file: " << filePath);
        return "";
    }
}

int Utils::bitCount8(int value) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((value & 1) == 1) {
            count++;
        }
        value >>= 1;
    }

    return count;
}
