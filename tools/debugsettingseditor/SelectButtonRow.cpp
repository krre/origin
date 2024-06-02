#include "SelectButtonRow.h"
#include <QPushButton>

SelectButtonRow::SelectButtonRow() {
    auto selectButton = new QPushButton(tr("Select All"));
    connect(selectButton, &QPushButton::clicked, this, &SelectButtonRow::select);

    auto unselectButton = new QPushButton(tr("Unselect All"));
    connect(unselectButton, &QPushButton::clicked, this, &SelectButtonRow::unselect);

    auto resetButton = new QPushButton(tr("Reset"));
    connect(resetButton, &QPushButton::clicked, this, &SelectButtonRow::reset);

    addWidget(selectButton);
    addWidget(unselectButton);
    addWidget(resetButton);
    addStretch(1);
}
