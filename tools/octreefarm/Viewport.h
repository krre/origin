#pragma once
#include "OctreeEditor.h"
#include "Camera.h"
#include <cstdint>
#include <QWindow>
#include <QVector3D>

const int LOD_PIXEL_LIMIT = 1;

class RenderEngine;

class Viewport : public QWindow {
    Q_OBJECT
public:
    struct LineVertex {
        glm::vec4 position;
        glm::vec4 color;
    };

    Viewport(OctreeEditor* octreeEditor = nullptr);
    ~Viewport();

    void reset();
    void deselect();
    void update();
    bool getIsReady() { return m_isReady; }

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

signals:
    void ready();
    void selectionChanged(bool selected);

public slots:
    void setShadeless(bool shadeless);

private slots:
    void onOctreeChanged();
    void onCameraStateChanged();

private:
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

    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    void addLineCube();
    void drawSelection();
    void pickOctree(const QPoint& pos);
    bool intersectRayAabb(const glm::vec3& origin, const glm::vec3& direction, const AABB& aabb);

    RenderEngine* m_renderEngine = nullptr;
    float m_rotateSpeed = 5;
    float m_panSpeed = 100;
    QPoint m_lastPos = QPoint();
    float m_rx = 0;
    float m_ry = 0;
    OctreeEditor* m_octreeEditor = nullptr;
    Camera m_camera;
    QVector3D m_backgroundColor = QVector3D(0.77, 0.83, 0.83);
    bool m_pickMode = false;
    QPoint m_pick;
    bool m_isReady = false;
    QVector<LineVertex> m_lines;
};
