#include "GeneralTab.h"
#include "ui_GeneralTab.h"

GeneralTab::GeneralTab() :
        ui(new Ui::GeneralTab) {
    ui->setupUi(this);
}

GeneralTab::~GeneralTab() {
    delete ui;
}
