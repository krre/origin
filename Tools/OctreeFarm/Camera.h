#pragma once
#include <QObject>

class Camera : public QObject {
    Q_OBJECT

public:
    explicit Camera(QObject* parent = 0);
};
