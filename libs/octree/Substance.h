#pragma once
#include <core/Object.h>

namespace Octree {

class Substance : public Core::Object {

public:
    Substance();
    ~Substance();
    uint32_t id() const { return m_id; }

private:
    uint32_t m_id = 0;

};

}
