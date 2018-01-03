#include "GeneralTab.h"
#include "ui_GeneralTab.h"
#include <QJsonObject>

namespace Origin {

namespace DebugSettingsEditor {

GeneralTab::GeneralTab() :
        ui(new Ui::GeneralTab) {
    ui->setupUi(this);

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
    ui->comboBoxBackend->setCurrentIndex(settings["backend"].toInt());
}

QJsonObject GeneralTab::debugSettings() const {
    QJsonObject obj;
    obj["enable"] = QJsonValue(ui->checkBoxEnable->isChecked());
    obj["debugHud"] = QJsonValue(ui->checkBoxDebugHUD->isChecked());
    obj["screen"] = QJsonValue(ui->comboBoxScreen->currentIndex());
    obj["backend"] = QJsonValue(ui->comboBoxBackend->currentIndex());

    return obj;
}

QString GeneralTab::name() const {
    return "general";
}

void GeneralTab::on_comboBoxScreen_currentIndexChanged(int currentIndex) {
    Q_UNUSED(currentIndex)
    emit flush();
}

void GeneralTab::on_comboBoxBackend_currentIndexChanged(int currentIndex) {
    Q_UNUSED(currentIndex)
    emit flush();
}

} // DebugSettingsEditor

} // Origin
