#include "Application.h"
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    // Hack to fix styling with Qt 6.5 on GTK3
    qunsetenv("GNOME_DESKTOP_SESSION_ID");
    qunsetenv("XDG_CURRENT_DESKTOP");

    Application app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
