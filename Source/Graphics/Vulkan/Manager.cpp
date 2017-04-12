#include "Manager.h"
#include "../../Core/App.h"
#include "../../Event/Event.h"
#include "../../Scene/SceneManager.h"
#include "Swapchain.h"

using namespace Vulkan;

Manager::~Manager() {
    Instance::get()->release();
}

void Manager::init() {
    new Instance();
    Instance* instance = Instance::get();
    instance->create();
}

void Manager::onWindowResize(int width, int height) {

}
