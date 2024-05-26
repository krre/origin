#pragma once
#include "Core/SingleObject.h"

class Logger : public Core::SingleObject<Logger> {

public:
    Logger(Object* parent = nullptr);
};
