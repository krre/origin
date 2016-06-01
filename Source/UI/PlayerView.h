#pragma once
#include "View.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Scene.h"
#include "../Process/ProcessManager.h"

class PlayerView : public View {

public:
    PlayerView();

private:
    shared_ptr<Camera> camera;
    shared_ptr<Scene> scene;
    ProcessManager processManager;
};
