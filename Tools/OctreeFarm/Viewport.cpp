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

Viewport::Viewport(OctreeEditor* octree) : octree(octree) {
    setFlag(Qt::FramelessWindowHint);
//    connect(octree, &Octree::dataChanged, this, &Viewport::onOctreeChanged);
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
