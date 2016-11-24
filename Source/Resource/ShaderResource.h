#pragma once
#include "Resource.h"
#include <vector>

class ShaderResource : public Resource {

public:
    ShaderResource();
    void load(const std::string& path) override;
    std::vector<char> getBuffer() const { return buffer; }

private:
    std::vector<char> buffer;
};
