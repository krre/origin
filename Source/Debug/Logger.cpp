#include "Logger.h"

static Origin::Logger* instance = nullptr;

namespace Origin {

Logger::Logger(Object* parent) : Object(parent) {
    instance = this;
}

} // Origin
