#include "SVOBuilder.h"

SVOBuilder::SVOBuilder() {

}

std::vector<uint32_t> SVOBuilder::buildTest() {
    std::vector<uint32_t> data;
    // Header
    data.push_back(0x00000004); // => Block info
    // Nodes
    data.push_back(0x00027F08); // 0000 0000 0000 0010 | 0111 1111 | 0000 1000
    data.push_back(0x0002BF80); // 0000 0000 0000 0010 | 1011 1111 | 1000 0000
    data.push_back(0x00008F00); // 0000 0000 0000 0000 | 1000 1111 | 0000 0000
    // Block info
    data.push_back(0x00000000);
    // Attach data
    data.push_back(0x0000037F); // 0000 0000 0000 0000 0000 0003 | 0111 1111
    data.push_back(0x00000A99); // 0000 0000 0000 0000 0000 1010 | 1001 1001
    data.push_back(0x00000000); // 0000 0000 0000 0000 0000 0000 | 0000 0000
    // Colors
    data.push_back(0x044A00FF);
    data.push_back(0xA30000FF);
    data.push_back(0x13DAFFFF);
    data.push_back(0x7E4681FF);
    data.push_back(0xFF0011FF);
    data.push_back(0x903472FF);
    data.push_back(0xAD7D4DFF);

    data.push_back(0x5A1681FF);
    data.push_back(0x6B38ACFF);
    data.push_back(0x5DD772FF);
    data.push_back(0xC5651FFF);

    return data;
}
