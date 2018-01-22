#include "OptionsDialog.h"
#include <QtWidgets>

namespace OctreeFarm {

OptionsDialog::OptionsDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("Options"));
    setMinimumSize(400, 300);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(this, &OptionsDialog::accepted, this, &OptionsDialog::onAccepted);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

void OptionsDialog::onAccepted() {
    qDebug() << "accepted";
}

} // OctreeFarm
