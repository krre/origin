#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#include <nano-signal-slot/nano_signal_slot.hpp>

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

#define print(x) std::cout << x << std::endl;
#define error(x) std::cerr << x << std::endl;
