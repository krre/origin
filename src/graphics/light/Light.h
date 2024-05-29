#pragma once
#include <core/Object.h>

class Light : public Core::Object {

public:
    Light();

    bool getEnable() const { return enable; }
    void setEnable(bool enable);

protected:
    bool enable = true;

};