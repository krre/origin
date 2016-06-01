#pragma once
#include <functional>
#include <map>

// Based on http://simmesimme.github.io/tutorials/2015/09/20/signal-slot/
template <typename... Args>
class Signal {

public:
    Signal() {}

    int connect(std::function<void(Args...)> const& slot) const {
        slots.insert(std::make_pair(++currentId, slot));
        return currentId;
    }

    template <typename F, typename... A>
    int connectMember(F&& f, A&& ... a) const {
        slots.insert({ ++currentId, std::bind(f, a...) });
        return currentId;
    }

    void disconnect(int id) const { slots.erase(id); }

    void disconnectAll() const { slots.clear(); }

    void emit(Args... p) {
        for (auto it : slots) {
            it.second(p...);
        }
    }

    Signal& operator=(Signal const& other) {
        disconnectAll();
    }

private:
    mutable std::map<int, std::function<void(Args...)>> slots;
    mutable int currentId = 0;
};
