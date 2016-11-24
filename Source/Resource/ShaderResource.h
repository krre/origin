#pragma once
#include "Resource.h"
#include <vector>

class ShaderResource : public Resource {

public:
    ShaderResource();
    void load(const std::string& path) override;
    const char* getData() const { return buffer.data(); }
    int getSize() const { return buffer.size(); }

private:
    std::vector<char> buffer;
};
