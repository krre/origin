#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("OctreeFarm");
    app.setApplicationVersion("0.1.0");

    OctreeFarm::MainWindow window;
    window.show();

    return app.exec();
}
