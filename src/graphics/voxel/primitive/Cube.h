#pragma once
#include <octree/Octree.h>

class Cube : public Octree::Octree {
public:
    Cube(float width = 1.0, float height = 1.0, float depth = 1.0);

private:
    float m_width;
    float m_height;
    float m_depth;
};
