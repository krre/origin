#pragma once
#include "Object.h"
#include <assert.h>

namespace Core {

// Singleton that inherited from Object class
template <typename T>
class SingleObject : public Core::Object {
public:
    SingleObject(Object* parent = nullptr) : Object(parent) {
        assert(s_instance == nullptr && "SingleObject should be initialized only once");
        s_instance = static_cast<T*>(this);
    }

    virtual ~SingleObject() {
        s_instance = nullptr;
    }

    static T* get() {
        return s_instance;
    }

    static bool exists() {
        return s_instance != nullptr;
    }

    static void release() {
        if (s_instance != nullptr) {
            delete s_instance;
            s_instance = nullptr;
        }
    }

private:
    static T* s_instance;
};

template <typename T>
T* SingleObject<T>::s_instance = nullptr;

}
