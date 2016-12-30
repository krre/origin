#include "Debug.h"
#include "../Core/App.h"
#include "../Core/Utils.h"
#include <Covenantland.h>

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
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        // Ignore empty strings and strings with first '#' symbol
        if (line.size() && line.at(0) != '#') {
            std::vector<std::string> pair = Utils::split(line, '=');
            if (pair.size() != 2) {
                error("Failed to parse main.debug at line: " << line);
            } else {
                values[pair.at(0)] = pair.at(1);
            }
        }
    }

    for (auto value : values) {
        if (value.first == "enable") {
            enable = value.second == "true" ? true : false;
        }
    }
}
