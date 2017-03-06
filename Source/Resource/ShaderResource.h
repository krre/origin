#pragma once
#include "Resource.h"
#include <vector>

class ShaderResource : public Resource {

public:
    ShaderResource();
    void load(const std::string& path) override;
    const uint32_t* getData() const { return buffer.data(); }
    size_t getSize() const { return buffer.size(); }

private:
    std::vector<uint32_t> buffer;
};
