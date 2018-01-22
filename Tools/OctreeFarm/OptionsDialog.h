#pragma once
#include <QDialog>
#include <QDialogButtonBox>

namespace OctreeFarm {

class OptionsDialog : public QDialog {

public:
    OptionsDialog(QWidget* parent = 0);

private slots:
    void onAccepted();

private:
    QDialogButtonBox* buttonBox;
};

} // OctreeFarm
