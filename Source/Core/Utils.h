#pragma once
#include "../Core/Object.h"
#include "../Core/Common.h"
#include <glm/glm.hpp>

class Utils : public Object {

public:
    Utils();
    static std::string zeroFill(const std::string& number);
    static std::string getPathSeparator();
    static uint32 rgbaToUint32(const glm::vec4& color);
};
