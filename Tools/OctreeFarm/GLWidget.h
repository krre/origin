#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <cstdint>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void updateOctreeInGPU(int offset, void* data, int count);

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    GLuint objectsTexture;
    GLuint octreesTexture;
    GLuint objectsTbo;
    GLuint octreesTbo;
    QOpenGLShaderProgram program;
};
