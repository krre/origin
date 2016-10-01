#include "Properties.h"
#include <QtWidgets>

Properties::Properties(Octree* octree) :
    octree(octree) {
    QFormLayout* formlayout = new QFormLayout;
    setLayout(formlayout);

    colorButton = new QPushButton;
    nodeColor = QColor(Qt::red);
    colorButtonPal = colorButton->palette();
    colorButtonPal.setColor(QPalette::Button, nodeColor);
    colorButton->setPalette(colorButtonPal);
    colorButton->setAutoFillBackground(true);
    colorButton->setFlat(true);
    formlayout->addRow(tr("Color:"), colorButton);

    connect(colorButton, &QPushButton::clicked, this, &Properties::changeNodeColor);
}

void Properties::changeNodeColor() {
    QColor chosenColor = QColorDialog::getColor();
    colorButtonPal.setColor(QPalette::Button, chosenColor);
    colorButton->setPalette(colorButtonPal);
}
