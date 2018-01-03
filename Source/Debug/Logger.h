#pragma once
#include "Core/Singleton.h"

namespace Origin {

class Logger : public Singleton<Logger> {

public:
    Logger();
};

} // Origin
