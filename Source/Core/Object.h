#pragma once
#include "Defines.h"
#include "Signal.h"
#include <iostream>
#include <memory>

using namespace std;

class Object {

public:
    Object();
    void setName(const string& name) { this->name = name; }
    string getName() const { return name; }

private:
    string name;
};
