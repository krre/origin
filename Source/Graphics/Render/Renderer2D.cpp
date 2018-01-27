#include "Renderer2D.h"
#include "UI/Control.h"
#include "UI/View3D.h"
#include "VulkanRenderer/GpuBuffer.h"

namespace Origin {

Renderer2D::Renderer2D() {
    uint32_t startSize = 10000;
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);;
}

Renderer2D::~Renderer2D() {

}

void Renderer2D::render() {
    uint32_t size = vertices.size() * sizeof(UIBatch::Vertex);

    if (size > vertexBuffer->getSize()) {
        vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    }

    if (size) {
        vertexBuffer->write(vertices.data(), size);
    }
}

void Renderer2D::prepare(Control* control) {
    renderViews.clear();
    batches.clear();
    vertices.clear();
    if (control != nullptr) {
        getBatches(control, batches, vertices);
    }
}

void Renderer2D::getBatches(Control* control, std::vector<UIBatch>& batches, std::vector<UIBatch::Vertex>& vertices) {
    if (!control->getVisible()) return;

    View3D* view3d = dynamic_cast<View3D*>(control);
    if (view3d) {
        renderViews.push_back(view3d);
        return;
    }

    control->prepareBatch(batches, vertices);

    for (auto child : control->getChildren()) {
        if (child->getVisible()) {
            getBatches(child, batches, vertices);
        }
    }
}

} // Origin
