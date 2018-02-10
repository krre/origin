#pragma once
#include "Octree.h"
#include "Camera.h"
#include <cstdint>
#include <QWindow>
#include <QVector3D>

namespace OctreeFarm {

const int LOD_PIXEL_LIMIT = 1;

class RenderEngine;

class Viewport : public QWindow {
    Q_OBJECT

    struct PickResult {
        glm::vec3 pos;
        uint32_t parent;
        uint32_t scale;
        int childIdx;
    };

    struct DebugOut {
        glm::vec4 debugVec;
        int debugInt;
        float debugFloat;
    };

public:
    Viewport(Octree* octree = nullptr);
    ~Viewport();
    void updateOctreeInGPU(int offset, void* data, int count);
    void reset();
    bool getIsReady() { return isReady; }

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event);

signals:
    void ready();

public slots:
    void setShadeless(bool shadeless);

private slots:
    void onOctreeChanged();

private:
    RenderEngine* renderEngine;
    float rotateSpeed = 5;
    float panSpeed = 100;
    QPoint lastPos;
    float rx = 0;
    float ry = 0;
    Octree* octree;
    Camera camera;
    QVector3D backgroundColor = QVector3D(0.77, 0.83, 0.83);
    bool pickMode = false;
    QPoint pick;
    bool isReady = false;
};

} // OctreeFarm
