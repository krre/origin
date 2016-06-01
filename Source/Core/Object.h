#pragma once
#include "Signal.h"
#include <iostream>
#include <memory>

#define print(x) cout << x << endl;

using namespace std;

class Object {

public:
    Object();
    void setName(const string& name) { this->name = name; }
    string getName() const { return name; }

private:
    string name;
};
