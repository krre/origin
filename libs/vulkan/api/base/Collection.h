#pragma once
#include <vector>
#include <stdlib.h>

#define VULKAN_DESTROY_COLLECTION(f) { \
    if (!m_collection.empty()) { \
        (f); \
        m_collection.clear(); \
    } \
} \

namespace Vulkan {

template <typename T>
class Collection {
public:
    Collection() = default;

    size_t count() const { return m_collection.size(); }
    T at(size_t i) const { return m_collection.at(i); }
    const T* data() const { return m_collection.data(); }
    virtual void destroy() = 0;

protected:
    std::vector<T> m_collection;
};

}
