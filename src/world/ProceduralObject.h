#pragma once
#include <core/Object.h>

class ProceduralObject : public Core::Object {
public:
    ProceduralObject();
    virtual void make() = 0;

private:
    uint64_t m_seed;
    std::vector<uint32_t> m_data;
};
