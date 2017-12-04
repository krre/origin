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
    return QJsonObject();
}

QString GeneralTab::name() const {
    return "general";
}

void GeneralTab::on_comboBoxScreen_currentIndexChanged(int currentIndex) {
    Q_UNUSED(currentIndex)
    emit flush();
}
