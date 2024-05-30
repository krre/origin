#pragma once
#include <QDialog>

class QDialogButtonBox;

class Options : public QDialog {
    Q_OBJECT
public:
    Options();

private:
    QDialogButtonBox* m_buttonBox = nullptr;
};
