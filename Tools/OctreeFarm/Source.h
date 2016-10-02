#pragma once
#include <QObject>

class Source : public QObject {
    Q_OBJECT

public:
    explicit Source(QObject* parent = 0);
};
