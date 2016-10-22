#include "Octree.h"
#include "../../Core/Utils.h"
#include <fstream>
#include <bitset>

Octree::Octree() {

}

void Octree::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        error("Failed open file: " << path);
        return;
    }

    std::string text = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    source = json::parse(text);
}

void Octree::draw() {

}

std::shared_ptr<std::vector<uint32_t>> Octree::data() {
    auto data = std::make_shared<std::vector<uint32_t>>();

    // Append header
    data->push_back(0);

    std::vector<json::object_t*> octreesFirst;
    std::vector<json::object_t*> octreesSecond;

    json::object_t* parent = source.get_ptr<json::object_t*>();
    octreesFirst.push_back(parent);

    std::vector<uint32_t> colorDescriptors;
    std::vector<uint32_t> colors;
    uint32_t offset = 0;

//    std::cout << source.dump(4) << std::endl;

    // Append node descriptors
    while (true) {

        uint32_t nodeDescriptor = 0;
        uint32_t colorDescriptor = 0;
        octreesSecond.clear();
        json::object_t* octree = octreesFirst[0];
        octreesFirst.erase(octreesFirst.begin());

        for (auto& node: (*octree)) {
            nodeDescriptor |= (1 << (8 + std::stoi(node.first))); // Valid nodes

            json::iterator iter = node.second.find("children");
            if (iter != node.second.end()) {
                nodeDescriptor |= (1 << std::stoi(node.first)); // Non-leaf nodes
                octreesSecond.push_back(iter.value().get_ptr<json::object_t*>());
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
            if (data->size() == 1) { // First descriptor in vector
                nodeDescriptor |= (1 << 17); // Set offset to 1
            } else {
                uint32_t lastDescriptor = data->at(offset);
                nodeDescriptor |= ((lastDescriptor >> 17) + std::bitset<8>(lastDescriptor).count() - 1);
            }
        }

        data->push_back(nodeDescriptor);

        colorDescriptors.push_back(colorDescriptor);
        offset++;

        if (octreesFirst.empty()) {
            if (octreesSecond.empty()) {
                break;
            } else {
                octreesFirst = octreesSecond;
            }
        }
    }

    (*data)[0] = offset + 1; // Address to block info

    // Append block info
    data->push_back(0);

    // Append attach descriptors
    offset = colorDescriptors.size();
    for (int i = 0 ; i < colorDescriptors.size(); i++) {
        uint32_t colorDescriptor = colorDescriptors[i];
        int numColors = std::bitset<8>(colorDescriptor).count();
        if (numColors) {
            colorDescriptor |= (offset << 8);
            offset += numColors;
        }
        data->push_back(colorDescriptor);
    }

    // Append colors
    for (int i = 0; i < colors.size(); i++) {
        data->push_back(colors[i]);
    }

    return data;
}
