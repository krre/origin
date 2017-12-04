#include "GeneralTab.h"
#include "ui_GeneralTab.h"
#include <QJsonObject>

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

}

QJsonObject GeneralTab::debugSettings() const {
    QJsonObject obj;
    obj["enable"] = QJsonValue(ui->checkBoxEnable->isChecked());
    obj["debugHud"] = QJsonValue(ui->checkBoxDebugHUD->isChecked());
    obj["screen"] = QJsonValue(ui->comboBoxScreen->currentText());

    return obj;
}

QString GeneralTab::name() const {
    return "general";
}

void GeneralTab::on_comboBoxScreen_currentIndexChanged(int currentIndex) {
    Q_UNUSED(currentIndex)
    emit flush();
}
