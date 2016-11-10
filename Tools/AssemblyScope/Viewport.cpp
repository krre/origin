#include "Viewport.h"
#include <QtCore>

Viewport::Viewport() {
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    setFormat(format);
    setUpdateBehavior(QOpenGLWidget::PartialUpdate);
}

void Viewport::initializeGL() {

}

void Viewport::paintGL() {

}
