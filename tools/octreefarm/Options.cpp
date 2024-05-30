#include "Options.h"
#include <QtWidgets>

Options::Options() {
    m_buttonBox = new QDialogButtonBox;
    m_buttonBox->setOrientation(Qt::Horizontal);
    m_buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addStretch(1);
    verticalLayout->addWidget(m_buttonBox);
    setLayout(verticalLayout);

    resize(400, 300);
}
