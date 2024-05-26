#include "GeneralTab.h"
#include "ui_GeneralTab.h"
#include <QJsonObject>
#include <QtCore>

GeneralTab::GeneralTab() :
        ui(new Ui::GeneralTab) {
    ui->setupUi(this);

    QDir dir(QDir::currentPath() + "/Saves");
    for (const QString& name : dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        ui->comboBoxSave->addItem(name);
    }

    connect(ui->checkBoxEnable, &QCheckBox::toggled, this, &GeneralTab::flush);
    connect(ui->checkBoxDebugHUD, &QCheckBox::toggled, this, &GeneralTab::flush);
}

GeneralTab::~GeneralTab() {
    delete ui;
}

void GeneralTab::setDebugSettings(const QJsonObject& settings) {
    ui->checkBoxEnable->setChecked(settings["enable"].toBool());
    ui->checkBoxDebugHUD->setChecked(settings["debugHud"].toBool());
    ui->comboBoxScreen->setCurrentIndex(settings["screen"].toInt());
    ui->comboBoxSave->setCurrentText(settings["save"].toString());
    ui->comboBoxRenderer->setCurrentIndex(settings["renderer"].toInt());
}

QJsonObject GeneralTab::debugSettings() const {
    QJsonObject obj;
    obj["enable"] = QJsonValue(ui->checkBoxEnable->isChecked());
    obj["debugHud"] = QJsonValue(ui->checkBoxDebugHUD->isChecked());
    obj["screen"] = QJsonValue(ui->comboBoxScreen->currentIndex());
    obj["save"] = QJsonValue(ui->comboBoxSave->currentText());
    obj["renderer"] = QJsonValue(ui->comboBoxRenderer->currentIndex());

    return obj;
}

QString GeneralTab::name() const {
    return "general";
}

void GeneralTab::on_comboBoxScreen_currentIndexChanged(int currentIndex [[maybe_unused]]) {
    emit flush();
}

void GeneralTab::on_comboBoxSave_currentIndexChanged(int currentIndex [[maybe_unused]]) {
    emit flush();
}

void GeneralTab::on_comboBoxRenderer_currentIndexChanged(int currentIndex [[maybe_unused]]) {
    emit flush();
}
