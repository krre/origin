#include "Properties.h"
#include <QtWidgets>

Properties::Properties(Octree* octree) :
    octree(octree) {
    QFormLayout* formlayout = new QFormLayout;
    setLayout(formlayout);

    indexLabel = new QLabel;
    formlayout->addRow(tr("Index:"), indexLabel);

    colorButton = new QPushButton;
    colorButton->setAutoFillBackground(true);
    colorButton->setFlat(true);
    setNodeColor(QColor(Qt::blue));
    formlayout->addRow(tr("Color:"), colorButton);

    connect(colorButton, &QPushButton::clicked, this, &Properties::changeNodeColor);
    connect(octree, &Octree::nodeSelected, this, &Properties::onNodeSelected);
    connect(octree, &Octree::nodeDeselected, this, &Properties::onNodeDeselected);

    onNodeDeselected();
}

void Properties::setNodeIndex(int index) {
    if (index >= 0) {
        indexLabel->setText(QString::number(index));
    } else {
        indexLabel->setText(QString());
    }
}

void Properties::setNodeColor(const QColor& color) {

    QPalette colorButtonPal = colorButton->palette();
    colorButtonPal.setColor(QPalette::Button, color.isValid() ? color : QColor(Qt::transparent));
    colorButton->setPalette(colorButtonPal);
    nodeColor = color;

    colorButton->setEnabled(color.isValid());
}

void Properties::changeNodeColor() {
    QColor color = QColorDialog::getColor(nodeColor);
    setNodeColor(color);
    octree->changeNodeColor(color);
}

void Properties::onNodeSelected(int index, const QColor& color) {
    setNodeIndex(index);
    setNodeColor(color);
}

void Properties::onNodeDeselected() {
    setNodeIndex(-1);
    setNodeColor(QColor());
}
