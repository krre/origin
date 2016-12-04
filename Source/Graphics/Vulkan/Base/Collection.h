#pragma once
#include "Resulter.h"
#include <vector>

namespace Vulkan {

template<typename T> class Collection : public Resulter {

public:
    Collection() = default;
    int getCount() const { return collection.size(); }
    T at(size_t i) const { return collection.at(i); }
    T* data() const { return collection.data(); }

protected:
    std::vector<T> collection;
};

} // Vulkan
