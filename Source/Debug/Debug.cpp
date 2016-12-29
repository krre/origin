#include "Debug.h"
#include "../Core/App.h"
#include "../Core/Utils.h"
#include <Covenantland.h>

/*
Values in main.debug:
enable = true|false
scene = menu|world|settings
*/

Debug::Debug() {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

void Debug::setValue(const std::string& key, const std::string& value) {
    values[key] = value;
}

std::string Debug::getValue(const std::string& key) const {
    return values.at(key);
}

void Debug::loadValues() {
    std::string mainDebugPath = App::getCurrentPath() + "/Debug/main.debug";
    std::string mainDebugText = Utils::readTextFile(mainDebugPath);
    std::stringstream stream(mainDebugText);
    std::string line;

    while (std::getline(stream, line, '\n')) {
//        print(line)
    }
}
