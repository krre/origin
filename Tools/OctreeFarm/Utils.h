#pragma once
#include <QObject>

class Utils : public QObject {
    Q_OBJECT

public:
    explicit Utils(QObject *parent = 0);
    static int bitCount8(int value);

};
