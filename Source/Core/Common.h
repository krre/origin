#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#ifndef QT_VERSION
    #include <nano-signal-slot/nano_signal_slot.hpp>
#endif

#ifndef QT_VERSION
    #define print(x) std::cout << x << std::endl;
#endif

#ifndef QT_VERSION
    #define error(x) std::cerr << x << std::endl;
#endif

constexpr int pageBytes = 1 << 13; // 8192 (use in OctreeFarm)
const int blockInfoEnd = 1;
