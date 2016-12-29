#include "Debug.h"

Debug::Debug() {

}

void Debug::setValue(const std::string& key, const std::string& value) {
    values[key] = value;
}

std::string Debug::getValue(const std::string& key) const {
    return values.at(key);
}
