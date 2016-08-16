#pragma once
#include "Common.h"
#include <nano-signal-slot/nano_signal_slot.hpp>
#include <iostream>
#include <memory>

class Object {

public:
    Object();
    void setName(const std::string& name) { this->name = name; }
    std::string getName() const { return name; }

private:
    std::string name;
};
