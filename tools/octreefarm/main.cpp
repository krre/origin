#include "Application.h"
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    Application app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
