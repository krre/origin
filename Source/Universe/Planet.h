#pragma once
#include "ProceduralObject.h"

struct PlanetParameters {
    int radius;
};

class Planet : public ProceduralObject {

public:
    Planet(PlanetParameters parameters);

private:
    PlanetParameters parameters;
};
