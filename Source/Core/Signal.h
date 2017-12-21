#pragma once
#include <vector>
#include <functional>

template<class R, class... Args> class Signal {

public:
    void connect(std::function<R, Args...> target) {
        targets.push_back(target);
    }

    template<class... Args1> void fire(Args1... args) {
        for (const auto& target : targets) {
            target(args...);
        }
    }

private:
    std::vector<std::function<R, Args...>> targets;
};
