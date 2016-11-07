#include "Options.h"
#include <QtCore>

Options::Options(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("Options"));
    setMinimumSize(400, 300);
}
