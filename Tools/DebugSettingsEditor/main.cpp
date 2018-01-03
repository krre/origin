#include "MainWindow.h"
#include "Defines.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    Origin::DebugSettingsEditor::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
