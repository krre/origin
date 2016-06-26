#pragma once
#include "Object.h"
#include <assert.h>

template <typename T> class Singleton : public Object {

public:
    Singleton() {
        assert(instance == 0 && "Singleton object should be initialized only once");
        instance = static_cast<T*>(this);
    }

    virtual ~Singleton() {
        instance = nullptr;
    }

    static T* getInstance() {
        return instance;
    }

    void release() {
        if (this) {
            delete this;
            instance = nullptr;
        }
    }

private:
    static T* instance;
};

template <typename T> T* Singleton<T>::instance = nullptr;
