#pragma once
#include "../Core/Object.h"

class Utils : public Object {

public:
    Utils();
    static std::string zeroFill(const std::string& number);
    static std::string getPathSeparator();
};
