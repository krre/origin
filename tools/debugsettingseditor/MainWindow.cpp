#include "MainWindow.h"
#include "Application.h"
#include "ui_MainWindow.h"
#include "GeneralTab.h"
#include "VulkanTab.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tabWidget->addTab(new GeneralTab, tr("General"));
    ui->tabWidget->addTab(new VulkanTab, tr("Vulkan"));

    debugSettingsPath = QCoreApplication::applicationDirPath() + "/debug.json";

    readSettings();
    readDebugSettings();

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        AbstractTab* tab = qobject_cast<AbstractTab*>(ui->tabWidget->widget(i));
        connect(tab, &AbstractTab::flush, this, &MainWindow::writeDebugSettings);
    }

    writeDebugSettings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(Application::Title),
        tr("<h3>%1 %2</h3> \
           Debug settings editor for Origin game<br><br> \
           Based on Qt %3<br> \
           Build on %4 %5<br><br> \
           <a href=%6>%6</a><br><br>Copyright © %7, %8").
           arg(Application::Title, Application::Version, QT_VERSION_STR,
            Application::BuildDate, Application::BuildTime, Application::Url,
            Application::Years, Application::Author));
}

void MainWindow::on_actionReload_triggered() {
    readDebugSettings();
}

void MainWindow::readSettings() {
    QSettings settings;
    settings.beginGroup("MainWindow");

    if (!restoreGeometry(settings.value("geometry").toByteArray())) {
        resize(1200, 800);
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    ui->tabWidget->setCurrentIndex(settings.value("tab", 0).toInt());
    settings.endGroup();
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("tab", ui->tabWidget->currentIndex());
    settings.endGroup();
}

void MainWindow::readDebugSettings() {
    QFile file(debugSettingsPath);
    bool settingsExists = file.open(QIODevice::ReadOnly);

    QJsonDocument doc;
    if (settingsExists) {
        doc = QJsonDocument(QJsonDocument::fromJson(file.readAll()));
    }

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        AbstractTab* tab = qobject_cast<AbstractTab*>(ui->tabWidget->widget(i));
        if (settingsExists) {
            tab->setDebugSettings(doc.object()[tab->name()].toObject());
        } else {
            tab->setDefaultSettings();
        }
    }
}

void MainWindow::writeDebugSettings() {
    QFile file(debugSettingsPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file" << debugSettingsPath;
        return;
    }

    QJsonObject obj;

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        AbstractTab* tab = qobject_cast<AbstractTab*>(ui->tabWidget->widget(i));
        obj[tab->name()] = tab->debugSettings();
    }

    QJsonDocument doc(obj);
    file.write(doc.toJson());
}
