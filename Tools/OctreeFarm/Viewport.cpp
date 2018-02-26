#include "Viewport.h"
#include <QtWidgets>
#include "RenderEngine.h"
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
    update();
}

void Viewport::onOctreeChanged() {
    qDebug() << "onOctreeChanged";
    update();
}

void Viewport::onCameraStateChanged() {
    qDebug() << "onCameraStateChanged";
    if (!(width() || height())) return;

    float aspect = (float)(width() / height());
    qDebug() << aspect;
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    float rot = 0;
    model = glm::rotate(model, rot, glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(model, rot, glm::vec3(1.0, 1.0, 1.0));
    glm::mat4 mvp = proj * view * model;
    renderEngine->updateMvp(mvp);
    update();
}

void Viewport::reset() {
    rx = 0;
    ry = 0;
    camera.reset();
}

void Viewport::update() {
    qDebug() << "update";
    renderEngine->render();
}

void Viewport::setShadeless(bool shadeless) {
    Q_UNUSED(shadeless)
    update();
}

} // OctreeFarm
