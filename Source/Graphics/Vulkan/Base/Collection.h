#pragma once
#include "Object.h"
#include <vector>

namespace Vulkan {

template<typename T> class Collection : public Object {

public:
    Collection() = default;
    int getCount() const { return collection.size(); }
    T at(size_t i) const { return collection.at(i); }
    T* data() const { return collection.data(); }

protected:
    std::vector<T> collection;
};

} // Vulkan
