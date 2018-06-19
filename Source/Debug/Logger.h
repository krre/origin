#pragma once
#include "Core/SingleObject.h"

namespace Origin {

class Logger : public SingleObject<Logger> {

public:
    Logger(Object* parent = nullptr);
};

} // Origin
