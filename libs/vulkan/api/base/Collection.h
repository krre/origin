#pragma once
#include <vector>
#include <stdlib.h>

#define VULKAN_DESTROY_COLLECTION(f) { \
    if (!collection.empty()) { \
        (f); \
        collection.clear(); \
    } \
} \

namespace Vulkan {

template <typename T>
class Collection {
public:
    Collection() = default;
    bool isOwner() const { return owner; }
    size_t getCount() const { return collection.size(); }
    T at(size_t i) const { return collection.at(i); }
    const T* getData() const { return collection.data(); }
    virtual void destroy() = 0;

protected:
    std::vector<T> collection;
    bool owner = true; // Always true for collections
};

} // Vulkan
