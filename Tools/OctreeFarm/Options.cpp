#include "Options.h"
#include <QtWidgets>

Options::Options(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("Options"));
    setMinimumSize(400, 300);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(this, &Options::accepted, this, &Options::onAccepted);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

void Options::onAccepted() {
    qDebug() << "accepted";
}
