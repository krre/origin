#include "GeneralTab.h"
#include <QJsonObject>
#include <QtWidgets>

GeneralTab::GeneralTab() {
    enableCheckBox = new QCheckBox(tr("Use debug settings"));
    connect(enableCheckBox, &QCheckBox::toggled, this, &GeneralTab::flush);

    debugHudCheckBox = new QCheckBox(tr("Show debug HUD"));
    connect(debugHudCheckBox, &QCheckBox::toggled, this, &GeneralTab::flush);

    screenComboBox = new QComboBox;
    screenComboBox->addItems({ tr("Menu"), tr("Settings"), tr("Game"), tr("New Game"), tr("Load Game"), tr("Wait") });

    saveComboBox = new QComboBox;

    QDir dir(QDir::currentPath() + "/Saves");

    for (const QString& name : dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        saveComboBox->addItem(name);
    }

    rendererComboBox = new QComboBox;
    rendererComboBox->addItems({ tr("Polygonal"), tr("Raycast") });

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Default screen:"), screenComboBox);
    formLayout->addRow(tr("Save:"), saveComboBox);
    formLayout->addRow(tr("Renderer:"), rendererComboBox);

    formLayout->itemAt(formLayout->indexOf(screenComboBox))->setAlignment(Qt::AlignLeft);
    formLayout->itemAt(formLayout->indexOf(saveComboBox))->setAlignment(Qt::AlignLeft);
    formLayout->itemAt(formLayout->indexOf(rendererComboBox))->setAlignment(Qt::AlignLeft);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(enableCheckBox);
    verticalLayout->addWidget(debugHudCheckBox);
    verticalLayout->addLayout(formLayout);
    verticalLayout->addStretch();

    setLayout(verticalLayout);
}

void GeneralTab::setDebugSettings(const QJsonObject& settings) {
    enableCheckBox->setChecked(settings["enable"].toBool());
    debugHudCheckBox->setChecked(settings["debugHud"].toBool());
    screenComboBox->setCurrentIndex(settings["screen"].toInt());
    saveComboBox->setCurrentText(settings["save"].toString());
    rendererComboBox->setCurrentIndex(settings["renderer"].toInt());
}

QJsonObject GeneralTab::debugSettings() const {
    QJsonObject obj;
    obj["enable"] = QJsonValue(enableCheckBox->isChecked());
    obj["debugHud"] = QJsonValue(debugHudCheckBox->isChecked());
    obj["screen"] = screenComboBox->currentIndex();
    obj["save"] = QJsonValue(saveComboBox->currentText());
    obj["renderer"] = QJsonValue(rendererComboBox->currentIndex());

    return obj;
}

QString GeneralTab::name() const {
    return "general";
}
