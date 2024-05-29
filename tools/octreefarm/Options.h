#pragma once
#include <QDialog>

namespace Ui {
    class Options;
}

class Options : public QDialog {
    Q_OBJECT
public:
    Options();
    ~Options();

private:
    Ui::Options* ui;
};
