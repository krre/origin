#pragma once
#include "View.h"
#include "../Graphics3D/Camera.h"
#include "../Graphics3D/Scene.h"
#include "../Process/ProcessManager.h"
#include <memory>

class PlayerView : public View {

public:
    PlayerView();

private:
    shared_ptr<Camera> camera;
    shared_ptr<Scene> scene;
    ProcessManager processManager;
};
