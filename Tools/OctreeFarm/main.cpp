#include "MainWindow.h"
#include "Constants.h"
#include "Settings.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(Constants::App::NAME);
    app.setApplicationVersion(Constants::App::VERSION);

    OctreeFarm::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
