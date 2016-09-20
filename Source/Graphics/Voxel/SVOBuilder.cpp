#include "SVOBuilder.h"

SVOBuilder::SVOBuilder() {

}

std::shared_ptr<std::vector<uint32_t> > SVOBuilder::buildTest() {
    auto data = std::make_shared<std::vector<uint32_t>>();
    data->push_back(0x00007F00);
//    data->push_back(0x00000000);
    return data;
}
