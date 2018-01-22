#pragma once
#include <QObject>
#include <QWidget>

namespace AssemblyBox {

class Properties : public QWidget {
    Q_OBJECT
public:
    explicit Properties(QWidget* parent = 0);
};

} // AssemblyBox
