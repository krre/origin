#pragma once
#include "Core/Object.h"
#include "Graphics/GraphicsTypes.h"
#include <glm/glm.hpp>
#include <vector>
#include <json/json.hpp>

using json = nlohmann::json;

class Utils : public Object {

public:
    Utils();
    static std::string zeroFill(const std::string& number);
    static std::string getPathSeparator();
    static uint32_t rgbaToUint32(const glm::vec4& color);
    static std::string readTextFile(const std::string& filePath);
    static uint32_t floatToUint(float value);
    static float uintToFloat(uint32_t value);
    static std::string uintToBinaryString(uint32_t value);
    static uint32_t binaryStringToUint(const std::string& value);
    static std::shared_ptr<std::vector<uint32_t>> jsonToBinary(json source);
    static std::vector<std::string> split(const std::string &value, char delim);
    static void removeChar(std::string& str, char c);
    static std::string graphicsBackendToString(GraphicsBackend backend);
};
