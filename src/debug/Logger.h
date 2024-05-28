#pragma once
#include <core/SingleObject.h>

class Logger : public Core::SingleObject<Logger> {

public:
    Logger(Object* parent = nullptr);
};
