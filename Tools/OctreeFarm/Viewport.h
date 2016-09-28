#pragma once
#include "Octree.h"
#include "Camera.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <cstdint>

class Viewport : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    Viewport(Octree* octree);
    void updateOctreeInGPU(int offset, void* data, int count);
    void reset();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

signals:
    void ready();

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    GLuint objectsTexture;
    GLuint octreesTexture;
    GLuint objectsTbo;
    GLuint octreesTbo;
    QOpenGLShaderProgram program;

    float rotateSpeed = 5;
    QPoint lastPos;
    float rx = 0;
    float ry = 0;
    Octree* octree;
    Camera camera;
    QVector3D backgroundColor = QVector3D(0.77, 0.83, 0.83);
};
