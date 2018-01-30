#pragma once
#include <QDialog>

namespace Ui {
    class Options;
}

namespace OctreeFarm {

class Options : public QDialog {
    Q_OBJECT

public:
    explicit Options(QWidget* parent = 0);
    ~Options();

private:
    Ui::Options* ui;
};

} // OctreeFarm
