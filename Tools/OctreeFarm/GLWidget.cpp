#include "GLWidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {

}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.95, 1.0, 1.0, 1.0);
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
