#include "Plane.h"

Plane::Plane(float width, float height) : m_width(width), m_height(height) {
    setVertices({
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f,
    });

    setIndices({ 0, 1, 2, 2, 3, 0 });
}
