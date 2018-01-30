#include "MainWindow.h"
#include "Defines.h"
#include "Settings.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    OctreeFarm::Settings::init(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, &app);

    OctreeFarm::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
