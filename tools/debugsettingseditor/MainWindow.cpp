#include "MainWindow.h"
#include "Application.h"
#include "GeneralTab.h"
#include "VulkanTab.h"
#include <QtWidgets>

MainWindow::MainWindow() {
    m_tabWidget = new QTabWidget;
    m_tabWidget->addTab(new GeneralTab, tr("General"));
    m_tabWidget->addTab(new VulkanTab, tr("Vulkan"));

    setCentralWidget(m_tabWidget);

    m_debugSettingsPath = QCoreApplication::applicationDirPath() + "/debug.json";

    createActions();

    readSettings();
    readDebugSettings();

    for (int i = 0; i < m_tabWidget->count(); i++) {
        AbstractTab* tab = qobject_cast<AbstractTab*>(m_tabWidget->widget(i));
        connect(tab, &AbstractTab::flush, this, &MainWindow::writeDebugSettings);
    }

    writeDebugSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::about() {
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

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Reload"), this, &MainWindow::reload);
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", Qt::CTRL | Qt::Key_Q, this, qOverload<>(&QMainWindow::close));

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::about);
}

void MainWindow::reload() {
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

    m_tabWidget->setCurrentIndex(settings.value("tab", 0).toInt());
    settings.endGroup();
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("tab", m_tabWidget->currentIndex());
    settings.endGroup();
}

void MainWindow::readDebugSettings() {
    QFile file(m_debugSettingsPath);
    bool settingsExists = file.open(QIODevice::ReadOnly);

    QJsonDocument doc;
    if (settingsExists) {
        doc = QJsonDocument(QJsonDocument::fromJson(file.readAll()));
    }

    for (int i = 0; i < m_tabWidget->count(); i++) {
        AbstractTab* tab = qobject_cast<AbstractTab*>(m_tabWidget->widget(i));

        if (settingsExists) {
            tab->setDebugSettings(doc.object()[tab->name()].toObject());
        } else {
            tab->setDefaultSettings();
        }
    }
}

void MainWindow::writeDebugSettings() {
    QFile file(m_debugSettingsPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file" << m_debugSettingsPath;
        return;
    }

    QJsonObject obj;

    for (int i = 0; i < m_tabWidget->count(); i++) {
        AbstractTab* tab = qobject_cast<AbstractTab*>(m_tabWidget->widget(i));
        obj[tab->name()] = tab->debugSettings();
    }

    QJsonDocument doc(obj);
    file.write(doc.toJson());
}
