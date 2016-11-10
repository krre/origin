#pragma once
#include <QDialog>
#include <QDialogButtonBox>

class Options : public QDialog {

public:
    Options(QWidget* parent = 0);

private slots:
    void onAccepted();

private:
    QDialogButtonBox* buttonBox;
};
