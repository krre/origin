#pragma once
#include <core/Object.h>

class Light : public Core::Object {

public:
    Light();

    bool enable() const { return m_enable; }
    void setEnable(bool enable);

protected:
    bool m_enable = true;

};
