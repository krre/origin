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
