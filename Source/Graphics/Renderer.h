#pragma once
#include "../Core/Singleton.h"

class Renderer : public Singleton<Renderer> {

public:
    Renderer();
    void render();
};
