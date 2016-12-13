#pragma once

class Scene {

public:
    Scene();
    virtual void draw(float dt) = 0;
    virtual void update(float dt) = 0;

protected:
    virtual void onWindowResize(int width, int height) = 0;
};
