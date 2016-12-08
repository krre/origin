#include <GL/glew.h>
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
    glewExperimental = GL_TRUE;
    glewInit();
    glClearColor(0.95, 1.0, 1.0, 1.0);
}

void Viewport::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
