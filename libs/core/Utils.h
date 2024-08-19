#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <json/json.hpp>

namespace Core {

namespace Utils {
    using json = nlohmann::json;

    std::string zeroFill(const std::string& number);
    std::string getPathSeparator();
    uint32_t rgbaToUint32(const glm::vec4& color);
    std::string readTextFile(const std::string& filePath);
    uint32_t floatToUint(float value);
    float uintToFloat(uint32_t value);
    std::string uintToBinaryString(uint32_t value);
    uint32_t binaryStringToUint(const std::string& value);
    std::shared_ptr<std::vector<uint32_t>> jsonToBinary(json source);
    std::vector<std::string> split(const std::string &value, char delim);
    void removeChar(std::string& str, char c);
}

}
