#pragma once
#include "Resource.h"

class ShaderResource : public Resource {

public:
    ShaderResource();
    void load(const std::string& path) override;
};
