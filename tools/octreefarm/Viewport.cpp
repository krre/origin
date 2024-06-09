#include "Viewport.h"
#include "RenderEngine.h"
#include "vulkan/GpuBuffer.h"
#include "octree/Octree.h"
#include "MainWindow.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <QtWidgets>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

Viewport::Viewport(OctreeEditor* octreeEditor) : m_octreeEditor(octreeEditor) {
    setFlag(Qt::FramelessWindowHint);

    connect(&m_camera, &Camera::stateChanged, this, &Viewport::onCameraStateChanged);
    connect(octreeEditor, &OctreeEditor::dataChanged, this, &Viewport::onOctreeChanged);

    WId windowHandle = winId();
#if defined(Q_OS_LINUX)
    auto x11Application = qGuiApp->nativeInterface<QNativeInterface::QX11Application>();
    m_renderEngine = new RenderEngine(x11Application->connection(), &windowHandle, this);
#elif defined(Q_OS_WIN)
    renderEngine = new RenderEngine(GetModuleHandle(nullptr), (void*)(windowHandle), this);
#endif

    m_renderEngine->create();

}

Viewport::~Viewport() {

}

void Viewport::mousePressEvent(QMouseEvent* event) {
    m_lastPos = event->pos();

    if (event->button() == Qt::LeftButton) {
        pickOctree(event->pos());
    }
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::RightButton) {
        m_rx += (m_lastPos.x() - event->pos().x()) / m_rotateSpeed;
        m_ry += (m_lastPos.y() - event->pos().y()) / m_rotateSpeed;
        m_camera.rotate(m_rx, m_ry);
    } else if (event->buttons() == Qt::MiddleButton) {
        float dx = (m_lastPos.x() - event->pos().x()) / m_panSpeed;
        float dy = (event->pos().y() - m_lastPos.y()) / m_panSpeed;
        m_camera.pan(dx, dy);
    }

    m_lastPos = event->pos();
}

void Viewport::wheelEvent(QWheelEvent* event) {
    m_camera.zoom(glm::sin(event->angleDelta().ry()));
    update();
}

void Viewport::resizeEvent(QResizeEvent* event [[maybe_unused]]) {
    // Hack to fix crash on Qt 5.11.1
    if (!m_renderEngine || MainWindow::isClosing()) return;

    m_renderEngine->resize();
    m_camera.resize(event->size().width(), event->size().height());
    // update() do not use here because it already done by camera state changing.
}

void Viewport::onOctreeChanged() {
    uint32_t size = m_octreeEditor->octree()->vertices().size() * sizeof(Octree::Octree::Vertex);
    if (size) {
        m_renderEngine->setVoxelVertextCount(m_octreeEditor->octree()->vertices().size());
        m_renderEngine->voxelVertexBuffer()->write(m_octreeEditor->octree()->vertices().data(), size);
        m_renderEngine->markDirty();
        update();
    }
}

void Viewport::onCameraStateChanged() {
    if (!(width() || height())) return;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = m_camera.projective() * m_camera.view() * model;
    m_renderEngine->updateMvp(mvp);
    update();
}

void Viewport::addLineCube() {
    LineVertex vertex = {};
    vertex.color = { 1.0, 1.0, 0.0, 1.0 };

    // Front top
    vertex.position = { -1.0, 1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { 1.0, 1.0, 1.0, 1.0 }; m_lines.push_back(vertex);

    // Front right
    vertex.position = { 1.0, 1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { 1.0, -1.0, 1.0, 1.0 }; m_lines.push_back(vertex);

    // Front bottom
    vertex.position = { 1.0, -1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { -1.0, -1.0, 1.0, 1.0 }; m_lines.push_back(vertex);

    // Front left
    vertex.position = { -1.0, -1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { -1.0, 1.0, 1.0, 1.0 }; m_lines.push_back(vertex);

    // Back top
    vertex.position = { -1.0, 1.0, -1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { 1.0, 1.0, -1.0, 1.0 }; m_lines.push_back(vertex);

    // Back right
    vertex.position = { 1.0, 1.0, -1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { 1.0, -1.0, -1.0, 1.0 }; m_lines.push_back(vertex);

    // Back bottom
    vertex.position = { 1.0, -1.0, -1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { -1.0, -1.0, -1.0, 1.0 }; m_lines.push_back(vertex);

    // Back left
    vertex.position = { -1.0, -1.0, -1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { -1.0, 1.0, -1.0, 1.0 }; m_lines.push_back(vertex);

    // Top left
    vertex.position = { -1.0, 1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { -1.0, 1.0, -1.0, 1.0 }; m_lines.push_back(vertex);

    // Top rigth
    vertex.position = { 1.0, 1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { 1.0, 1.0, -1.0, 1.0 }; m_lines.push_back(vertex);

    // Bottom left
    vertex.position = { -1.0, -1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { -1.0, -1.0, -1.0, 1.0 }; m_lines.push_back(vertex);

    // Bottom rigth
    vertex.position = { 1.0, -1.0, 1.0, 1.0 }; m_lines.push_back(vertex);
    vertex.position = { 1.0, -1.0, -1.0, 1.0 }; m_lines.push_back(vertex);
}

void Viewport::drawSelection() {
    m_renderEngine->setLineVertextCount(m_lines.size());
    if (m_lines.size()) {
        m_renderEngine->lineVertexBuffer()->write(m_lines.data(), sizeof(LineVertex) * m_lines.size());
    }
    m_renderEngine->markDirty();
    update();
}

void Viewport::pickOctree(const QPoint& pos) {
    m_pick = pos;
    m_pickMode = true;

    float x = (2.0f * pos.x()) / width() - 1.0f;
    float y = 1.0f - (2.0f * pos.y()) / height();
    glm::vec2 ndcRay = glm::vec2(x, y);
    glm::vec4 clipRay = glm::vec4(ndcRay, -1.0, 1.0);
    glm::vec4 eyeRay = glm::inverse(m_camera.projective()) * clipRay;
    eyeRay = glm::vec4(eyeRay.x, eyeRay.y, -1.0, 0.0);

    glm::vec3 worldRay = glm::vec3(glm::inverse(m_camera.view()) * eyeRay);
    worldRay = glm::normalize(worldRay);

    m_lines.clear();

    bool result = intersectRayAabb(m_camera.position(), worldRay, { glm::vec3(-1.0, -1.0, -1.0), glm::vec3(1.0, 1.0, 1.0) });
    if (result) {
        addLineCube();
    }

    drawSelection();
    emit selectionChanged(result);
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
    m_rx = 47;
    m_ry = -35;
    m_camera.reset();
    m_camera.setPosition(glm::vec3(0, 0, -5));
    m_camera.rotate(m_rx, m_ry);
    deselect();
}

void Viewport::deselect() {
    m_lines.clear();
    drawSelection();
    emit selectionChanged(false);
}

void Viewport::update() {
    m_renderEngine->render();
}

void Viewport::setShadeless(bool shadeless) {
    m_renderEngine->updateShadeless(shadeless);
    update();
}
