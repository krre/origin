#include "Properties.h"
#include "Command.h"
#include "OctreeEditor.h"
#include "Viewport.h"
#include <QtWidgets>

Properties::Properties(OctreeEditor* octree, Viewport* viewport, QUndoStack* undoStack, QWidget* parent)
    : QWidget(parent), octree(octree), viewport(viewport), undoStack(undoStack) {
    createUi();
    setNodeColor(QColor(Qt::blue));

    connect(octree, &OctreeEditor::nodeSelected, this, &Properties::onNodeSelected);
    connect(octree, &OctreeEditor::nodeDeselected, this, &Properties::onNodeDeselected);

    onNodeDeselected();
}

void Properties::setNodeLevel(int level) {
    levelLabel->setText(level >= 0 ? QString::number(23 - level) : QString());
}

void Properties::setNodeIndex(int index) {
    indexLabel->setText(index >= 0 ? QString::number(index) : QString());
}

void Properties::setNodeColor(const QColor& color) {
    QPalette colorButtonPal = colorButton->palette();
    colorButtonPal.setColor(QPalette::Button, color.isValid() ? color : QColor(Qt::transparent));
    colorButton->setPalette(colorButtonPal);
    nodeColor = color;
    colorButton->setEnabled(color.isValid());
}

void Properties::setShadeless(bool shadeless) {
    shadelessCheckBox->setChecked(shadeless);
}

bool Properties::shadeless() const {
    return shadelessCheckBox->isChecked();
}

void Properties::changeNodeColor() {
    QColor color = QColorDialog::getColor(nodeColor);

    if (color.isValid()) {
        setNodeColor(color);
        QUndoCommand* changeColorCommand = new ChangeColorCommand(octree, color);
        undoStack->push(changeColorCommand);
    }
}

void Properties::onNodeSelected(int level, int index, const QColor& color) {
    setNodeLevel(level);
    setNodeIndex(index);
    setNodeColor(color);
}

void Properties::onNodeDeselected() {
    setNodeLevel(-1);
    setNodeIndex(-1);
    setNodeColor(QColor());
}

void Properties::levelPlus() {
    qDebug() << "level plus";
}

void Properties::levelMinus() {
    qDebug() << "level minus";
}

void Properties::levelReset() {
    qDebug() << "level reset";
}

void Properties::createUi() {
    auto plusButton = new QPushButton(tr("Level+"));
    connect(plusButton, &QPushButton::clicked, this, &Properties::levelPlus);

    auto minusButton = new QPushButton(tr("Level-"));
    connect(minusButton, &QPushButton::clicked, this, &Properties::levelMinus);

    auto resetButton = new QPushButton(tr("Reset"));
    connect(resetButton, &QPushButton::clicked, this, &Properties::levelReset);

    auto levelLayout = new QHBoxLayout;
    levelLayout->addWidget(plusButton);
    levelLayout->addWidget(minusButton);
    levelLayout->addWidget(resetButton);

    levelLabel = new QLabel;
    indexLabel = new QLabel;

    colorButton = new QPushButton;
    colorButton->setFlat(true);
    colorButton->setAutoFillBackground(true);
    connect(colorButton, &QPushButton::clicked, this, &Properties::changeNodeColor);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Level:"), levelLabel);
    formLayout->addRow(tr("Index:"), indexLabel);
    formLayout->addRow(tr("Color:"), colorButton);

    shadelessCheckBox = new QCheckBox(tr("Shadeless"));
    connect(shadelessCheckBox, &QCheckBox::stateChanged, viewport, &Viewport::setShadeless);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addLayout(levelLayout);
    verticalLayout->addLayout(formLayout);
    verticalLayout->addWidget(shadelessCheckBox);
    verticalLayout->addStretch();

    setLayout(verticalLayout);
}
