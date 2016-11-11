#include "Planet.h"

Planet::Planet(PlanetParameters parameters) : parameters(parameters) {
    print(parameters.radius)
}
