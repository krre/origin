#include "Viewport.h"
#include <QtWidgets>
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

#ifdef Q_OS_LINUX
#include <qpa/qplatformnativeinterface.h>
#include <QtPlatformHeaders/qxcbwindowfunctions.h>
#endif

namespace OctreeFarm {

Viewport::Viewport(Octree* octree) : octree(octree) {
    setFlag(Qt::FramelessWindowHint);
//    connect(octree, &Octree::dataChanged, this, &Viewport::onOctreeChanged);
#if defined(Q_OS_LINUX)
    QPlatformNativeInterface* native = QGuiApplication::platformNativeInterface();
    WId window = winId();
    renderEngine = QSharedPointer<RenderEngine>(new RenderEngine(native->nativeResourceForWindow("connection", this), &window));
#elif defined(Q_OS_WIN)
    renderEngine = QSharedPointer<RenderEngine>(new RenderEngine(GetModuleHandle(nullptr), (void*)(winId())));
#endif

    renderEngine->create();
}

Viewport::~Viewport() {

}

void Viewport::mousePressEvent(QMouseEvent* event) {
    lastPos = event->pos();

    if (event->button() == Qt::LeftButton) {
//        program.bind();
        pick = event->pos();
//        program.setUniformValue("pickPixel", QPoint(pick.x(), height() - pick.y()));
        pickMode = true;
        // Update is asynchronous action so selection is continued in paintGL()
//        update();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::RightButton) {
        rx += (lastPos.x() - event->pos().x()) / rotateSpeed;
        ry += (lastPos.y() - event->pos().y()) / rotateSpeed;
        camera.rotate(rx, ry);
//        update();
    } else if (event->buttons() == Qt::MiddleButton) {
        float dx = (lastPos.x() - event->pos().x()) / panSpeed;
        float dy = (event->pos().y() - lastPos.y()) / panSpeed;
        camera.pan(dx, dy);
//        update();
    }

    lastPos = event->pos();
}

void Viewport::wheelEvent(QWheelEvent* event) {
    camera.zoom(glm::sin(event->angleDelta().ry()));
    //    update();
}

void Viewport::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event)
    renderEngine->resize();
    renderEngine->render();
}

void Viewport::onOctreeChanged() {
    updateOctreeInGPU(0, octree->data(), sizeof(uint32_t) * octree->count());
//    update();
}

void Viewport::updateOctreeInGPU(int offset, void* data, int count) {

}

void Viewport::reset() {
    rx = 0;
    ry = 0;
    camera.reset();
}

void Viewport::setShadeless(bool shadeless) {
//    update();
}

} // OctreeFarm
