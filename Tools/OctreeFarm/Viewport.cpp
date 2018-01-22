#include <GL/glew.h>
#include "Viewport.h"
#include <QApplication>
#include <QMouseEvent>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

Viewport::Viewport(Octree* octree) : octree(octree) {
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    setFormat(format);

    setUpdateBehavior(QOpenGLWidget::PartialUpdate);

    connect(octree, &Octree::dataChanged, this, &Viewport::onOctreeChanged);
}

void Viewport::initializeGL() {
    glewExperimental = GL_TRUE;
    glewInit();
    glClearColor(0.95, 1.0, 1.0, 1.0);

    QString shaderDirPath = QApplication::applicationDirPath() + "/Data/Shader";
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, shaderDirPath + "/Voxel.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, shaderDirPath + "/Voxel.frag");
    program.bindAttributeLocation("vertex", 0);
    program.link();
    program.bind();

//    program.setUniformValue("pageBytes", pageBytes);
//    program.setUniformValue("blockInfoEnd", blockInfoEnd);
    program.setUniformValue("backgroundColor", backgroundColor);
    program.setUniformValue("pickPixel", QPoint(-1, -1));

    vbo.create();
    vbo.bind();
    GLfloat vertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  1.0f,
         1.0f, -1.0f,
    };
    vbo.allocate(vertices, sizeof(vertices));

    vao.create();
    vao.bind();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &octreesSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, octreesSsbo);
//    glBufferData(GL_SHADER_STORAGE_BUFFER, pageBytes, NULL, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, octreesSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glGenBuffers(1, &pickResultSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pickResultSsbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(PickResult), NULL, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, pickResultSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glGenBuffers(1, &renderListSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, renderListSsbo);
    int size = sizeof(int) * 2; // count + one offset
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, renderListSsbo);
    // Count
    size = sizeof(int);
    GLvoid* data = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, GL_MAP_WRITE_BIT);
    int count = 1;
    memcpy(data, &count, size);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    // Render list
    size = sizeof(uint32_t);
    int offset = 0;
    data = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, sizeof(int), size, GL_MAP_WRITE_BIT);
    memcpy(data, &offset, size);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glGenBuffers(1, &debugSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, debugSsbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(DebugOut), NULL, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 10, debugSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    isReady = true;
    emit ready();
}

void Viewport::paintGL() {
    QVector<glm::vec4> transform;
    transform.append(octree->octreeToWorld()[0]);
    transform.append(octree->octreeToWorld()[1]);
    transform.append(octree->octreeToWorld()[2]);
    transform.append(octree->octreeToWorld()[3]);

    glm::mat4 cameraToOctree = octree->worldToOctree() * camera.getCameraToWorld();
    transform.append(cameraToOctree[3]);

    glm::vec4 up = glm::vec4(camera.up(), 0.0);
    glm::vec4 look = glm::vec4(camera.look(), 0.0);
    glm::vec4 right = glm::vec4(camera.right(), 0.0);

    // Ray calculation is based on Johns Hopkins presentation:
    // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
    glm::vec4 h0 = look - up * glm::tan(camera.fov()); // min height vector
    glm::vec4 h1 = look + up * glm::tan(camera.fov()); // max height vector
    glm::vec4 stepH = (h1 - h0) / height();
    h0 += stepH / 2;

    glm::vec4 w0 = look - right * glm::tan(camera.fov()) * width() / height(); // min width vector
    glm::vec4 w1 = look + right * glm::tan(camera.fov()) * width() / height(); // max width vector
    glm::vec4 stepW = (w1 - w0) / width();
    w0 += stepW / 2;

    glm::vec4 startCornerPos = w0 + h0;

    transform.append(startCornerPos);
    transform.append(stepW);
    transform.append(stepH);

    int size = sizeof(glm::vec4) * transform.size();
//    int offset = pageBytes - size;
//    updateOctreeInGPU(offset, transform.data(), size);

    program.bind();

    QVector3D lightColor = QVector3D(1.0, 1.0, 1.0);
    QVector3D lightPos = QVector3D(1.5, 2.5, 1.0);

    program.setUniformValue("lightColor", lightColor);
    program.setUniformValue("lightPos", lightPos);
    program.setUniformValue("ambientStrength", 0.1f);
    program.setUniformValue("transformCount", transform.size());
    program.setUniformValue("frameWidth", width());
    program.setUniformValue("frameHeight", height());

    float lod = LOD_PIXEL_LIMIT * camera.fov() / height();
    program.setUniformValue("lod", glm::tan(lod));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    if (pickMode) {
        PickResult pickResult;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, pickResultSsbo);
        glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(pickResult), &pickResult);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        if (pickResult.parent == 0) {
            octree->deselect();
        } else {
            octree->select(pickResult.parent, pickResult.scale, pickResult.childIdx, pickResult.pos, QGuiApplication::keyboardModifiers() == Qt::ShiftModifier);
        }

        program.setUniformValue("pickPixel", QPoint(-1, -1));
        pickMode = false;
    }

    DebugOut debugOut;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, debugSsbo);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(debugOut), &debugOut);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

//    qDebug() << debugOut.debugInt;
//    qDebug() << debugOut.debugFloat;
//    qDebug() << QString::fromStdString(glm::to_string(debugOut.debugVec));
}

void Viewport::resizeGL(int w, int h) {
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Viewport::mousePressEvent(QMouseEvent* event) {
    lastPos = event->pos();

    if (event->button() == Qt::LeftButton) {
        program.bind();
        pick = event->pos();
        program.setUniformValue("pickPixel", QPoint(pick.x(), height() - pick.y()));
        pickMode = true;
        // Update is asynchronous action so selection is continued in paintGL()
        update();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::RightButton) {
        rx += (lastPos.x() - event->pos().x()) / rotateSpeed;
        ry += (lastPos.y() - event->pos().y()) / rotateSpeed;
        camera.rotate(rx, ry);
        update();
    } else if (event->buttons() == Qt::MiddleButton) {
        float dx = (lastPos.x() - event->pos().x()) / panSpeed;
        float dy = (event->pos().y() - lastPos.y()) / panSpeed;
        camera.pan(dx, dy);
        update();
    }

    lastPos = event->pos();
}

void Viewport::wheelEvent(QWheelEvent* event) {
    camera.zoom(glm::sin(event->angleDelta().ry()));
    update();
}

void Viewport::onOctreeChanged() {
    updateOctreeInGPU(0, octree->data(), sizeof(uint32_t) * octree->count());
    update();
}

void Viewport::updateOctreeInGPU(int offset, void* data, int count) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, octreesSsbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, count, data);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Viewport::reset() {
    rx = 0;
    ry = 0;
    camera.reset();
}

void Viewport::setShadeless(bool shadeless) {
    program.bind();
    program.setUniformValue("shadeless", shadeless);
    update();
}
