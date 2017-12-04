#include "GeneralTab.h"
#include "ui_GeneralTab.h"
#include <QJsonObject>

GeneralTab::GeneralTab() :
        ui(new Ui::GeneralTab) {
    ui->setupUi(this);
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
