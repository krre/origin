#pragma once
#include <QOpenGLWidget>

class Viewport : public QOpenGLWidget {
    Q_OBJECT

public:
    Viewport();

protected:
    void initializeGL() override;
    void paintGL() override;
};
