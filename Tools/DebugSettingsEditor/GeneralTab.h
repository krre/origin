#pragma once
#include <QWidget>

namespace Ui {
    class GeneralTab;
}

class GeneralTab : public QWidget {
    Q_OBJECT

public:
    explicit GeneralTab();
    ~GeneralTab();

private:
    Ui::GeneralTab* ui;
};
