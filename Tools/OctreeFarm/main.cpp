#include "MainWindow.h"
#include "Constants.h"
#include "Settings.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    // Hack to fix styling with Qt 6.5 on GTK3
    qunsetenv("GNOME_DESKTOP_SESSION_ID");
    qunsetenv("XDG_CURRENT_DESKTOP");

    QApplication app(argc, argv);
    app.setApplicationName(Constants::App::NAME);
    app.setApplicationVersion(Constants::App::VERSION);

    OctreeFarm::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
