#include "Properties.h"
#include "Command.h"
#include "OctreeEditor.h"
#include "Viewport.h"
#include "ui_Properties.h"
#include <QtWidgets>

Properties::Properties(OctreeEditor* octree, Viewport* viewport, QUndoStack* undoStack, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Properties),
    octree(octree),
    viewport(viewport),
    undoStack(undoStack) {
    ui->setupUi(this);
    ui->pushButtonColor->setAutoFillBackground(true);
    setNodeColor(QColor(Qt::blue));

    connect(ui->pushButtonColor, &QPushButton::clicked, this, &Properties::changeNodeColor);
    connect(ui->checkBoxShadeless, &QCheckBox::stateChanged, viewport, &Viewport::setShadeless);
    connect(octree, &OctreeEditor::nodeSelected, this, &Properties::onNodeSelected);
    connect(octree, &OctreeEditor::nodeDeselected, this, &Properties::onNodeDeselected);
    connect(ui->pushButtonPlus, &QPushButton::clicked, this, &Properties::levelPlus);
    connect(ui->pushButtonMinus, &QPushButton::clicked, this, &Properties::levelMinus);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &Properties::levelReset);

    onNodeDeselected();
}

Properties::~Properties() {
    delete ui;
}

void Properties::setNodeLevel(int level) {
    if (level >= 0) {
        ui->labelLevel->setText(QString::number(23 - level));
    } else {
        ui->labelLevel->setText(QString());
    }
}

void Properties::setNodeIndex(int index) {
    if (index >= 0) {
        ui->labelIndex->setText(QString::number(index));
    } else {
        ui->labelIndex->setText(QString());
    }
}

void Properties::setNodeColor(const QColor& color) {
    QPalette colorButtonPal = ui->pushButtonColor->palette();
    colorButtonPal.setColor(QPalette::Button, color.isValid() ? color : QColor(Qt::transparent));
    ui->pushButtonColor->setPalette(colorButtonPal);
    nodeColor = color;
    ui->pushButtonColor->setEnabled(color.isValid());
}

void Properties::setShadeless(bool shadeless) {
    ui->checkBoxShadeless->setChecked(shadeless);
}

bool Properties::getShadeless() const {
    return ui->checkBoxShadeless->isChecked();
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
