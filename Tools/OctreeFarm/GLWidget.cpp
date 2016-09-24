#include "GLWidget.h"
#include <QtCore>

GLWidget::GLWidget(QWidget* parent) :
    QOpenGLWidget(parent),
    objectsTexture(QOpenGLTexture::TargetBuffer),
    octreesTexture(QOpenGLTexture::TargetBuffer) {
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.95, 1.0, 1.0, 1.0);

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

    f->glGenBuffers(1, &objectsTbo);
    f->glBindBuffer(GL_TEXTURE_BUFFER, objectsTbo);
    f->glBufferData(GL_TEXTURE_BUFFER, 100, NULL, GL_STATIC_DRAW);

    f->glGenBuffers(1, &octreeTbo);
    f->glBindBuffer(GL_TEXTURE_BUFFER, octreeTbo);
    f->glBufferData(GL_TEXTURE_BUFFER, 100, NULL, GL_STATIC_DRAW);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::resizeGL(int w, int h) {
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
    Q_UNUSED(event)
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
    Q_UNUSED(event)
}

void GLWidget::updateOctreeInGPU(int offset, void* data, int count) {
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glBindBuffer(GL_TEXTURE_BUFFER, octreeTbo);
    f->glBufferSubData(GL_TEXTURE_BUFFER, offset, count, data);
}
