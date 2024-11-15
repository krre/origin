#include "Properties.h"
#include "Command.h"
#include "OctreeEditor.h"
#include "Viewport.h"
#include <QtWidgets>

Properties::Properties(OctreeEditor* octree, Viewport* viewport, QUndoStack* undoStack, QWidget* parent)
    : QWidget(parent), m_octree(octree), m_viewport(viewport), m_undoStack(undoStack) {
    createUi();
    setNodeColor(QColor(Qt::blue));

    connect(octree, &OctreeEditor::nodeSelected, this, &Properties::onNodeSelected);
    connect(octree, &OctreeEditor::nodeDeselected, this, &Properties::onNodeDeselected);

    onNodeDeselected();
}

void Properties::setNodeLevel(int level) {
    m_levelLabel->setText(level >= 0 ? QString::number(23 - level) : QString());
}

void Properties::setNodeIndex(int index) {
    m_indexLabel->setText(index >= 0 ? QString::number(index) : QString());
}

void Properties::setNodeColor(const QColor& color) {
    QPalette colorButtonPal = m_colorButton->palette();
    colorButtonPal.setColor(QPalette::Button, color.isValid() ? color : QColor(Qt::transparent));
    m_colorButton->setPalette(colorButtonPal);
    m_nodeColor = color;
    m_colorButton->setEnabled(color.isValid());
}

void Properties::setShadeless(bool shadeless) {
    m_shadelessCheckBox->setChecked(shadeless);
}

bool Properties::shadeless() const {
    return m_shadelessCheckBox->isChecked();
}

void Properties::changeNodeColor() {
    QColor color = QColorDialog::getColor(m_nodeColor);

    if (color.isValid()) {
        setNodeColor(color);
        QUndoCommand* changeColorCommand = new ChangeColorCommand(m_octree, color);
        m_undoStack->push(changeColorCommand);
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

    m_levelLabel = new QLabel;
    m_indexLabel = new QLabel;

    m_colorButton = new QPushButton;
    m_colorButton->setFlat(true);
    m_colorButton->setAutoFillBackground(true);
    connect(m_colorButton, &QPushButton::clicked, this, &Properties::changeNodeColor);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Level:"), m_levelLabel);
    formLayout->addRow(tr("Index:"), m_indexLabel);
    formLayout->addRow(tr("Color:"), m_colorButton);

    m_shadelessCheckBox = new QCheckBox(tr("Shadeless"));
    connect(m_shadelessCheckBox, &QCheckBox::checkStateChanged, m_viewport, &Viewport::setShadeless);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addLayout(levelLayout);
    verticalLayout->addLayout(formLayout);
    verticalLayout->addWidget(m_shadelessCheckBox);
    verticalLayout->addStretch();

    setLayout(verticalLayout);
}
