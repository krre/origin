#pragma once
#include "Object.h"
#include <assert.h>

namespace Core {

// Singleton that inherited from Object class
template <typename T>
class SingleObject : public Core::Object {
public:
    SingleObject(Object* parent = nullptr) : Object(parent) {
        assert(instance == nullptr && "SingleObject should be initialized only once");
        instance = static_cast<T*>(this);
    }

    virtual ~SingleObject() {
        instance = nullptr;
    }

    static T* get() {
        return instance;
    }

    static bool exists() {
        return instance != nullptr;
    }

    static void release() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

private:
    static T* instance;
};

template <typename T>
T* SingleObject<T>::instance = nullptr;

} // Origin
