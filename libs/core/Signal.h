#pragma once
#include <map>
#include <functional>

namespace Core {

// Based on article http://simmesimme.github.io/tutorials/2015/09/20/signal-slot
template <class... Args>
class Signal {
public:
    // Connect method of class T
    template <class T>
    int connect(T* obj, void(T::*func)(Args...)) {
        return connect([=](Args... args) {
            (obj->*func)(args...);
        });
    }

    // Connect constant method of class T
    template <class T>
    int connect(T* obj, void(T::*func)(Args...)) const {
        return connect([=](Args... args) {
            (obj->*func)(args...);
        });
    }

    // Connect std::function object
    int connect(std::function<void(Args...)> const& target) const {
        m_targets.insert(std::make_pair(++m_currentId, target));
        return m_currentId;
    }

    void disconnect(int id) {
        m_targets.erase(id);
    }

    void disconnectAll() {
        m_targets.clear();
    }

    void fire(Args... args) {
        for (const auto& it : m_targets) {
            it.second(args...);
        }
    }

private:
    mutable std::map<int, std::function<void(Args...)>> m_targets;
    mutable int m_currentId = -1;
};

}
