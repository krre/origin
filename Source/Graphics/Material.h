#pragma once
#include "../Core/Object.h"
#include "Color.h"

class Material : public Object {

public:
    Material();

private:
    Color color;
};
