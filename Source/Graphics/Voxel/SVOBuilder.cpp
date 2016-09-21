#include "SVOBuilder.h"

SVOBuilder::SVOBuilder() {

}

std::shared_ptr<std::vector<uint32_t> > SVOBuilder::buildTest() {
    auto data = std::make_shared<std::vector<uint32_t>>();
//    data->push_back(0x00000000);
    data->push_back(0x00027F00); // 0000 0000 0000 0010 | 0111 1111 | 0100 0000
    data->push_back(0x00006F00); // 0000 0000 0000 0000 | 0110 1111 | 0000 0000
    return data;
}
