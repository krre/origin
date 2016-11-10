#pragma once
#include <QDialog>
#include <QDialogButtonBox>

class OptionsDialog : public QDialog {

public:
    OptionsDialog(QWidget* parent = 0);

private slots:
    void onAccepted();

private:
    QDialogButtonBox* buttonBox;
};
