#pragma once
#include "../Core/Object.h"

struct PlanetParameters {
    int radius;
};

class Planet : public Object {

public:
    Planet(PlanetParameters parameters);

private:
    PlanetParameters parameters;
};
