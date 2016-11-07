#include "Options.h"
#include <QtCore>

Options::Options(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("Options"));
    resize(400, 300);
}
