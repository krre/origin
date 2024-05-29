#include "Options.h"
#include "ui_Options.h"

Options::Options() : ui(new Ui::Options) {
    ui->setupUi(this);
}

Options::~Options() {
    delete ui;
}
