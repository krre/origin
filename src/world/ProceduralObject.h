#pragma once
#include <core/Object.h>
#include <memory>

class ProceduralObject : public Core::Object {
public:
    ProceduralObject();
    virtual void make() = 0;

private:
    uint64_t m_seed;
    std::shared_ptr<std::vector<uint32_t>> m_data;
};
