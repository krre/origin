#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("AssemblyBox");
    app.setApplicationVersion("0.1.0");

    AssemblyBox::MainWindow window;
    window.show();

    return app.exec();
}
