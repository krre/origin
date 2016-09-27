#include "Viewport.h"
#include <QtGui>
#include <QApplication>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

Viewport::Viewport(Octree* octree) : octree(octree) {
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    setFormat(format);

    camera.setPosition(glm::vec3(0.0, 0.0, 3.0));
    camera.setTarget(glm::vec3(0.0, 0.0, 0.0));
}

void Viewport::initializeGL() {
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
    glBufferData(GL_TEXTURE_BUFFER, sizeof(glm::vec4) * 100, NULL, GL_STATIC_DRAW);

    glGenTextures(1, &objectsTexture);
    glBindTexture(GL_TEXTURE_BUFFER, objectsTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, objectsTbo);

    glGenBuffers(1, &octreesTbo);
    glBindBuffer(GL_TEXTURE_BUFFER, octreesTbo);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(uint32_t) * 100, NULL, GL_STATIC_DRAW);

    glGenTextures(1, &octreesTexture);
    glBindTexture(GL_TEXTURE_BUFFER, octreesTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8UI, octreesTbo);

    emit ready();
}

void Viewport::paintGL() {

    QVector<glm::vec4> object;
    object.push_back(octree->octreeToWorld()[0]);
    object.push_back(octree->octreeToWorld()[1]);
    object.push_back(octree->octreeToWorld()[2]);
    object.push_back(octree->octreeToWorld()[3]);

    glm::mat4 cameraToOctree = octree->worldToOctree() * camera.cameraToWorld();

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(cameraToOctree, scale, rotation, translation, skew, perspective);

    object.push_back(glm::vec4(translation.x, translation.y, translation.z, 1.0));

    glm::vec3 up = camera.up();
    glm::vec3 look = camera.look();
    glm::vec3 right = camera.right();

    // Ray calculation is based on Johns Hopkins presentation:
    // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
    glm::vec3 h0 = look - up * glm::tan(camera.fov()); // min height vector
    glm::vec3 h1 = look + up * glm::tan(camera.fov()); // max height vector
    glm::vec3 stepH = (h1 - h0) / height();
    h0 += stepH / 2;

    glm::vec3 w0 = look - right * glm::tan(camera.fov()) * width() / height(); // min width vector
    glm::vec3 w1 = look + right * glm::tan(camera.fov()) * width() / height(); // max width vector
    glm::vec3 stepW = (w1 - w0) / width();
    w0 += stepW / 2;

    glm::vec3 startCornerPos = w0 + h0;

    object.push_back(glm::vec4(startCornerPos.x, startCornerPos.y, startCornerPos.z, 0.0));
    object.push_back(glm::vec4(stepW.x, stepW.y, stepW.z, 0.0));
    object.push_back(glm::vec4(stepH.x, stepH.y, stepH.z, 0.0));

    glm::vec3 octreeColor = glm::vec3(0.0, 1.0, 0.0);
    object.push_back(glm::vec4(octreeColor.x, octreeColor.y, octreeColor.z, 1.0));

    glBindBuffer(GL_TEXTURE_BUFFER, objectsTbo);
    glBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof(glm::vec4) * object.size(), object.data());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.bind();

    QVector3D lightColor = QVector3D(1.0, 1.0, 1.0);
    QVector3D lightPos = QVector3D(1.5, 2.5, 1.0);

    program.setUniformValue("lightColor", lightColor);
    program.setUniformValue("lightPos", lightPos);
    program.setUniformValue("ambientStrength", 0.1f);
    program.setUniformValue("objectCount", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, objectsTexture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, octreesTexture);

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Viewport::resizeGL(int w, int h) {
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Viewport::mousePressEvent(QMouseEvent* event) {
    lastPos = event->pos();
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
    if (QGuiApplication::mouseButtons() == Qt::RightButton) {
        rx += (lastPos.x() - event->pos().x()) / rotateSpeed;
        ry += (lastPos.y() - event->pos().y()) / rotateSpeed;
        lastPos = event->pos();
        camera.rotate(rx, ry);
        update();
    }
}

void Viewport::wheelEvent(QWheelEvent* event) {
    camera.zoom(glm::sin(event->angleDelta().ry()));
    update();
}

void Viewport::updateOctreeInGPU(int offset, void* data, int count) {
    glBindBuffer(GL_TEXTURE_BUFFER, octreesTbo);
    glBufferSubData(GL_TEXTURE_BUFFER, offset, count, data);
}
