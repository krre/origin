#pragma once
#include "Camera.h"
#include "OctreeEditor.h"
#include <QVulkanInstance>
#include <QVulkanWindow>
#include <QVector3D>

constexpr auto LodPixelLimit = 1;

class RenderEngine;

class Viewport final : public QVulkanWindow {
    Q_OBJECT
public:
    struct LineVertex {
        glm::vec4 position;
        glm::vec4 color;
    };

    explicit Viewport(OctreeEditor* octreeEditor = nullptr);
    ~Viewport() override;

    void reset();
    void deselect();
    void update();
    bool isReady() const;

protected:
    QVulkanWindowRenderer* createRenderer() override;
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
    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    void addLineCube();
    void drawSelection();
    void pickOctree(const QPoint& pos);
    bool intersectRayAabb(const glm::vec3& origin, const glm::vec3& direction, const AABB& aabb);

    QVulkanInstance m_vulkanInstance;
    RenderEngine* m_renderEngine = nullptr;
    float m_rotateSpeed = 5;
    float m_panSpeed = 100;
    QPoint m_lastPos = QPoint();
    float m_rx = 0;
    float m_ry = 0;
    OctreeEditor* m_octreeEditor = nullptr;
    Camera m_camera;
    QVector3D m_backgroundColor = QVector3D(0.77, 0.83, 0.83);
    QVector<LineVertex> m_lines;
};
