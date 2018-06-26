#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Defines.h"
#include "GeneralTab.h"
#include "VulkanTab.h"
#include <QtWidgets>

namespace DebugSettingsEditor {

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tabWidget->addTab(new GeneralTab, tr("General"));
    ui->tabWidget->addTab(new VulkanTab, tr("Vulkan"));

    settingsPath = QApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME;
    debugSettingsPath = QCoreApplication::applicationDirPath() + "/" + DEBUG_SETTINGS_NAME;

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
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br> \
           Copyright © 2017-2018, Vladimir Zarypov").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).arg(__DATE__).arg(APP_URL));
}

void MainWindow::on_actionReload_triggered() {
    readDebugSettings();
}

void MainWindow::readSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");

    if (!restoreGeometry(settings.value("geometry").toByteArray())) {
        resize(WINDOW_WIDTH, WINDOW_HEIGHT);
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    ui->tabWidget->setCurrentIndex(settings.value("tab", 0).toInt());
    settings.endGroup();
}

void MainWindow::writeSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("tab", ui->tabWidget->currentIndex());
    settings.endGroup();
}

void MainWindow::readDebugSettings() {
    QFile file(debugSettingsPath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        AbstractTab* tab = qobject_cast<AbstractTab*>(ui->tabWidget->widget(i));
        tab->setDebugSettings(doc.object()[tab->name()].toObject());
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

} // DebugSettingsEditor
