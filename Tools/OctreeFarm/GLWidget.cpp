#include "GLWidget.h"
#include <QtCore>
#include <QApplication>
#include <glm/glm.hpp>

GLWidget::GLWidget(QWidget* parent) :
    QOpenGLWidget(parent) {
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.95, 1.0, 1.0, 1.0);

    QString shaderDirPath = QApplication::applicationDirPath() + "/Data/Shader";
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, shaderDirPath + "/Voxel.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, shaderDirPath + "/Voxel.frag");
    program.bindAttributeLocation("vertex", 0);
    program.link();
    program.bind();

    program.setUniformValue("backgroundColor", backgroundColor);
    program.setUniformValue("objectStride", 9);
    program.setUniformValue("objects", 0);
    program.setUniformValue("octrees", 1);

    vbo.create();
    vbo.bind();
    GLfloat vertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  1.0f,

        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
    };
    vbo.allocate(vertices, sizeof(vertices));

    vao.create();
    vao.bind();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &objectsTbo);
    glBindBuffer(GL_TEXTURE_BUFFER, objectsTbo);
    glBufferData(GL_TEXTURE_BUFFER, 100, NULL, GL_STATIC_DRAW);

    glGenBuffers(1, &objectsTexture);
    glBindTexture(GL_TEXTURE_BUFFER, objectsTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, objectsTbo);

    glGenBuffers(1, &octreesTbo);
    glBindBuffer(GL_TEXTURE_BUFFER, octreesTbo);
    glBufferData(GL_TEXTURE_BUFFER, 100, NULL, GL_STATIC_DRAW);

    glGenBuffers(1, &octreesTexture);
    glBindTexture(GL_TEXTURE_BUFFER, octreesTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8UI, octreesTbo);

    updateOctreeInGPU(0, octree.data(), octree.count());
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
    glBindBuffer(GL_TEXTURE_BUFFER, octreesTbo);
    glBufferSubData(GL_TEXTURE_BUFFER, offset, count, data);
}
