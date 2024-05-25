#include "MainWindow.h"
#include "Defines.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    // Hack to fix styling with Qt 6.5 on GTK3
    qunsetenv("GNOME_DESKTOP_SESSION_ID");
    qunsetenv("XDG_CURRENT_DESKTOP");

    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    AssemblyBox::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
