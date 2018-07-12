#include "Viewport.h"
#include <QtWidgets>
#include "RenderEngine.h"
#include "Vulkan/GpuBuffer.h"
#include "Octree/Octree.h"
#include "MainWindow.h"
#define GLM_ENABLE_EXPERIMENTAL
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
        pickOctree(event->pos());
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
    // Hack to fix crash on Qt 5.11.1
    if (!renderEngine || MainWindow::isClosing()) return;

    renderEngine->resize();
    camera.resize(event->size().width(), event->size().height());
    // update() do not use here because it already done by camera state changing.
}

void Viewport::onOctreeChanged() {
    uint32_t size = octreeEditor->getOctree()->getVertices().size() * sizeof(Origin::Octree::Vertex);
    if (size) {
        renderEngine->setVoxelVertextCount(octreeEditor->getOctree()->getVertices().size());
        renderEngine->getVoxelVertexBuffer()->write(octreeEditor->getOctree()->getVertices().data(), size);
        renderEngine->markDirty();
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

    // Front top
    vertex.position = { -1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { 1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);

    // Front right
    vertex.position = { 1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { 1.0, -1.0, 1.0, 1.0 }; lines.push_back(vertex);

    // Front bottom
    vertex.position = { 1.0, -1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { -1.0, -1.0, 1.0, 1.0 }; lines.push_back(vertex);

    // Front left
    vertex.position = { -1.0, -1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { -1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);

    // Back top
    vertex.position = { -1.0, 1.0, -1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { 1.0, 1.0, -1.0, 1.0 }; lines.push_back(vertex);

    // Back right
    vertex.position = { 1.0, 1.0, -1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { 1.0, -1.0, -1.0, 1.0 }; lines.push_back(vertex);

    // Back bottom
    vertex.position = { 1.0, -1.0, -1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { -1.0, -1.0, -1.0, 1.0 }; lines.push_back(vertex);

    // Back left
    vertex.position = { -1.0, -1.0, -1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { -1.0, 1.0, -1.0, 1.0 }; lines.push_back(vertex);

    // Top left
    vertex.position = { -1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { -1.0, 1.0, -1.0, 1.0 }; lines.push_back(vertex);

    // Top rigth
    vertex.position = { 1.0, 1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { 1.0, 1.0, -1.0, 1.0 }; lines.push_back(vertex);

    // Bottom left
    vertex.position = { -1.0, -1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { -1.0, -1.0, -1.0, 1.0 }; lines.push_back(vertex);

    // Bottom rigth
    vertex.position = { 1.0, -1.0, 1.0, 1.0 }; lines.push_back(vertex);
    vertex.position = { 1.0, -1.0, -1.0, 1.0 }; lines.push_back(vertex);
}

void Viewport::drawSelection() {
    renderEngine->setLineVertextCount(lines.size());
    if (lines.size()) {
        renderEngine->getLineVertexBuffer()->write(lines.data(), sizeof(LineVertex) * lines.size());
    }
    renderEngine->markDirty();
    update();
}

void Viewport::pickOctree(const QPoint& pos) {
    pick = pos;
    pickMode = true;

    float x = (2.0f * pos.x()) / width() - 1.0f;
    float y = 1.0f - (2.0f * pos.y()) / height();
    glm::vec2 ndcRay = glm::vec2(x, y);
    glm::vec4 clipRay = glm::vec4(ndcRay, -1.0, 1.0);
    glm::vec4 eyeRay = glm::inverse(camera.getProjective()) * clipRay;
    eyeRay = glm::vec4(eyeRay.x, eyeRay.y, -1.0, 0.0);

    glm::vec3 worldRay = glm::vec3(glm::inverse(camera.getView()) * eyeRay);
    worldRay = glm::normalize(worldRay);

    lines.clear();

    bool result = intersectRayAabb(camera.getPosition(), worldRay, { glm::vec3(-1.0, -1.0, -1.0), glm::vec3(1.0, 1.0, 1.0) });
    if (result) {
        addLineCube();
    }

    drawSelection();
    selectionChanged(result);
}

bool Viewport::intersectRayAabb(const glm::vec3& origin, const glm::vec3& direction, const Viewport::AABB& aabb) {
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    glm::vec3 bounds[2];
    bounds[0] = aabb.min;
    bounds[1] = aabb.max;

    glm::vec3 invdir = 1.f / direction;
    glm::i8vec3 sign;

    sign.x = (invdir.x < 0);
    sign.y = (invdir.y < 0);
    sign.z = (invdir.z < 0);

    tmin = (bounds[sign.x].x - origin.x) * invdir.x;
    tmax = (bounds[1 - sign.x].x - origin.x) * invdir.x;
    tymin = (bounds[sign.y].y - origin.y) * invdir.y;
    tymax = (bounds[1 - sign.y].y - origin.y) * invdir.y;

    if ((tmin > tymax) || (tymin > tmax)) return false;

    if (tymin > tmin) {
        tmin = tymin;
    }

    if (tymax < tmax) {
        tmax = tymax;
    }

    tzmin = (bounds[sign.z].z - origin.z) * invdir.z;
    tzmax = (bounds[1 - sign.z].z - origin.z) * invdir.z;

    if ((tmin > tzmax) || (tzmin > tmax)) return false;

    if (tzmin > tmin) {
        tmin = tzmin;
    }

    if (tzmax < tmax) {
        tmax = tzmax;
    }

    return true;
}

void Viewport::reset() {
    rx = 47;
    ry = -35;
    camera.reset();
    camera.setPosition(glm::vec3(0, 0, -5));
    camera.rotate(rx, ry);
    deselect();
}

void Viewport::deselect() {
    lines.clear();
    drawSelection();
    emit selectionChanged(false);
}

void Viewport::update() {
    renderEngine->render();
}

void Viewport::setShadeless(bool shadeless) {
    renderEngine->updateShadeless(shadeless);
    update();
}

} // OctreeFarm
