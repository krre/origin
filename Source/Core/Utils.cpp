#include "Utils.h"
#include "Defines.h"
#include <fstream>
#include <bitset>

namespace Origin {

Utils::Utils() {

}

std::string Utils::zeroFill(const std::string& number) {
    return (number.size() == 1 ? "0" : "") + number;
}

std::string Utils::getPathSeparator() {
#if defined(OS_WIN)
    return "\\";
#elif defined(OS_LINUX)
    return "/";
#endif
}

uint32_t Utils::rgbaToUint32(const glm::vec4& color) {
    return (((int(color.r * 255) & 0xff) << 24) + ((int(color.g * 255) & 0xff) << 16) + ((int(color.b * 255) & 0xff) << 8) + (int(color.a * 255) & 0xff));
}

std::string Utils::readTextFile(const std::string& filePath) {
    std::ifstream in(filePath);
    if (in.is_open()) {
        std::string text((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
        return text;
    } else {
        throw std::runtime_error("Failed open file: " + filePath);
    }

    return "";
}

uint32_t Utils::floatToUint(float value) {
    return *(uint32_t*)&value;
}

float Utils::uintToFloat(uint32_t value) {
    return *(float*)&value;
}

std::string Utils::uintToBinaryString(uint32_t value) {
    return std::bitset<8>(value >> 24 & 0xFF).to_string() + " " +
           std::bitset<8>(value >> 16 & 0xFF).to_string() + " " +
           std::bitset<8>(value >> 8 & 0xFF).to_string() + " " +
            std::bitset<8>(value & 0xFF).to_string();
}

uint32_t Utils::binaryStringToUint(const std::string& value) {
    return uint32_t(std::bitset<32>(value).to_ullong());
}

std::shared_ptr<std::vector<uint32_t>> Utils::jsonToBinary(json source) {
    auto data = std::make_shared<std::vector<uint32_t>>();

    // Append header
    data->push_back(0);

    std::vector<json::object_t*> upLevel; // current parents
    std::vector<json::object_t*> downLevel; // childern for parents in upLevel

    json::object_t* root = source.get_ptr<json::object_t*>();
    upLevel.push_back(root);

    std::vector<uint32_t> colorDescriptors;
    std::vector<uint32_t> colors;
    uint32_t offset = 0;
    size_t upIndex = 0;

    // Append node descriptors
    while (upLevel.size()) {
        uint32_t nodeDescriptor = 0;
        uint32_t colorDescriptor = 0;
        json::object_t* octree = upLevel[upIndex];

        int downLevelIndex = downLevel.size(); // Save current position before new children will added

        for (auto& node: (*octree)) {
            nodeDescriptor |= (1 << (8 + std::stoi(node.first))); // Valid nodes

            json::iterator iter = node.second.find("children");
            if (iter != node.second.end()) {
                nodeDescriptor |= (1 << std::stoi(node.first)); // Non-leaf nodes
                downLevel.push_back(iter.value().get_ptr<json::object_t*>());
            }

            iter = node.second.find("color");
            if (iter != node.second.end()) {
                colorDescriptor |= (1 << std::stoi(node.first)); // Valid colors
                std::string nameColor = (*octree)[node.first]["color"];
                nameColor = nameColor.substr(1, nameColor.size() - 1);
                uint32_t color = std::stoul(nameColor, 0, 16);
                colors.push_back(color);
            }
        }

        int childNum = std::bitset<8>(nodeDescriptor).count();
        if (childNum) {
            int childrenOffset = upLevel.size() - upIndex + downLevelIndex;
            nodeDescriptor |= (childrenOffset << 17);
        }

        data->push_back(nodeDescriptor);
        colorDescriptors.push_back(colorDescriptor);

        offset++;
        upIndex++;

        if (upIndex == upLevel.size()) {
            upLevel = downLevel;
            downLevel.clear();
            upIndex = 0;
        }
    }

    (*data)[0] = offset + 1; // Address to block info

    // Append block info
    data->push_back(0);

    // Append attach descriptors
    offset = colorDescriptors.size();
    for (size_t i = 0 ; i < colorDescriptors.size(); i++) {
        uint32_t colorDescriptor = colorDescriptors[i];
        int numColors = std::bitset<8>(colorDescriptor).count();
        if (numColors) {
            colorDescriptor |= (offset << 8);
            offset += numColors;
        }
        data->push_back(colorDescriptor);
    }

    // Append colors
    for (size_t i = 0; i < colors.size(); i++) {
        data->push_back(colors[i]);
    }

    return data;
}

std::vector<std::string> Utils::split(const std::string& value, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss;
    ss.str(value);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.size()) {
            elems.push_back(item);
        }
    }

    return elems;
}

void Utils::removeChar(std::string& str, char c) {
    str.erase(remove(str.begin(), str.end(), c), str.end());
}

} // Origin
