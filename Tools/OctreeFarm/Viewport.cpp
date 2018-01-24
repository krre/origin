#include "Viewport.h"
#include <QApplication>
#include <QMouseEvent>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

namespace OctreeFarm {

Viewport::Viewport(Octree* octree) : octree(octree) {
//    connect(octree, &Octree::dataChanged, this, &Viewport::onOctreeChanged);
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
