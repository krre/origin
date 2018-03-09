#include "Viewport.h"
#include <QtWidgets>
#include "RenderEngine.h"
#include "Vulkan/GpuBuffer.h"
#include "Octree/Octree.h"
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

#if defined(Q_OS_LINUX)
    #include <QX11Info>
#endif

namespace OctreeFarm {

Viewport::Viewport(OctreeEditor* octreeEditor) : octreeEditor(octreeEditor) {
    setFlag(Qt::FramelessWindowHint);

    connect(&camera, &Camera::stateChanged, this, &Viewport::onCameraStateChanged);
    connect(octreeEditor, &OctreeEditor::dataChanged, this, &Viewport::onOctreeChanged);

    WId windowHandle = winId();
#if defined(Q_OS_LINUX)
    renderEngine = new RenderEngine(QX11Info::connection(), &windowHandle, this);
#elif defined(Q_OS_WIN)
    renderEngine = new RenderEngine(GetModuleHandle(nullptr), (void*)(windowHandle), this);
#endif

    renderEngine->create();
}

Viewport::~Viewport() {

}

void Viewport::mousePressEvent(QMouseEvent* event) {
    lastPos = event->pos();

    if (event->button() == Qt::LeftButton) {
        pick = event->pos();
        pickMode = true;
        lines.clear();
        addLineCube();
        renderEngine->setLineVertextCount(lines.size());
        renderEngine->getLineVertexBuffer()->write(lines.data(), sizeof(LineVertex) * lines.size());
        renderEngine->updateCommandBuffers();
        update();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::RightButton) {
        rx += (lastPos.x() - event->pos().x()) / rotateSpeed;
        ry += (lastPos.y() - event->pos().y()) / rotateSpeed;
        camera.rotate(rx, ry);
    } else if (event->buttons() == Qt::MiddleButton) {
        float dx = (lastPos.x() - event->pos().x()) / panSpeed;
        float dy = (event->pos().y() - lastPos.y()) / panSpeed;
        camera.pan(dx, dy);
    }

    lastPos = event->pos();
}

void Viewport::wheelEvent(QWheelEvent* event) {
    camera.zoom(glm::sin(event->angleDelta().ry()));
    update();
}

void Viewport::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event)
    renderEngine->resize();
    camera.resize(event->size().width(), event->size().height());
    // update() do not use here because it already done by camera state changing.
}

void Viewport::onOctreeChanged() {
    uint32_t size = octreeEditor->getOctree()->getVertices().size() * sizeof(Origin::Octree::Vertex);
    if (size) {
        renderEngine->setVoxelVertextCount(octreeEditor->getOctree()->getVertices().size());
        renderEngine->getVoxelVertexBuffer()->write(octreeEditor->getOctree()->getVertices().data(), size);
        renderEngine->updateCommandBuffers();
        update();
    }
}

void Viewport::onCameraStateChanged() {
    if (!(width() || height())) return;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = camera.getProjective() * camera.getView() * model;
    renderEngine->updateMvp(mvp);
    update();
}

void Viewport::addLineCube() {
    LineVertex vertex = {};
    vertex.color = { 1.0, 1.0, 0.0, 1.0 };

    vertex.position = { -1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { 1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);
}

void Viewport::reset() {
    rx = 47;
    ry = -35;
    camera.reset();
    camera.setPosition(glm::vec3(0, 0, -5));
    camera.rotate(rx, ry);
}

void Viewport::update() {
    renderEngine->render();
}

void Viewport::setShadeless(bool shadeless) {
    renderEngine->updateShadeless(shadeless);
    update();
}

} // OctreeFarm
