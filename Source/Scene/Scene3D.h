#pragma once

class Scene3D {

public:
    Scene3D();
    void draw(float dt);

private:
    void onWindowResize(int width, int height);
};
