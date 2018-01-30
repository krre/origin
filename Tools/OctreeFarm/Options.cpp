#include "Options.h"
#include "ui_Options.h"

namespace OctreeFarm {

Options::Options(QWidget* parent) : QDialog(parent),
        ui(new Ui::Options) {
    ui->setupUi(this);
}

Options::~Options() {
    delete ui;
}

} // OctreeFarm
