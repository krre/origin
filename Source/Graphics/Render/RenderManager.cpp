#include "RenderManager.h"
#include "Scene/Scene.h"
#include "UI/View.h"
#include "UI/Control.h"
#include "UI/Batch2D.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"

RenderManager::RenderManager() {

}

void RenderManager::renderView(View* view) {
    if (view->getScene()->getRootControl() == nullptr) return;

    std::vector<std::unique_ptr<Batch2D>> batches;
    VertexBuffer vertexBuffer(1000000);
    IndexBuffer indexBuffer(1000000);

    view->getScene()->getRootControl()->getBatches(batches, &vertexBuffer, &indexBuffer);
}
