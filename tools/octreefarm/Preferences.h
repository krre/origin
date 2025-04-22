#pragma once
#include <QDialog>

class QDialogButtonBox;

class Preferences : public QDialog {
    Q_OBJECT
public:
    Preferences();

private:
    QDialogButtonBox* m_buttonBox = nullptr;
};
