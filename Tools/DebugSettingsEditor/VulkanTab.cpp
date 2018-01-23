#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include "VulkanRenderer/API/Instance.h"
#include "VulkanRenderer/API/Device/PhysicalDevices.h"
#include "VulkanRenderer/API/Device/PhysicalDevice.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

namespace Origin {

namespace DebugSettingsEditor {

VulkanTab::VulkanTab() :
        ui(new Ui::VulkanTab) {
    ui->setupUi(this);

    connect(ui->groupBoxDebugReport, &QGroupBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxInformation, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxWarning, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxPerformance, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxError, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxDebug, &QCheckBox::toggled, this, &VulkanTab::flush);

    connect(ui->groupBoxLayers, &QGroupBox::toggled, this, &VulkanTab::flush);
    connect(ui->groupBoxExtensions, &QGroupBox::toggled, this, &VulkanTab::flush);

    connect(ui->listWidgetLayers, &QListWidget::itemSelectionChanged, this, &VulkanTab::flush);
    connect(ui->listWidgetExtensions, &QListWidget::itemSelectionChanged, this, &VulkanTab::flush);

    Vulkan::Instance instance;
    instance.create();

    Vulkan::PhysicalDevices physicalDevices(&instance);

    for (size_t i = 0; i < physicalDevices.getCount(); i++) {
        Vulkan::PhysicalDevice* physicalDevice = physicalDevices.getPhysicalDevice(i);
        ui->comboBoxDevice->insertItem(i, physicalDevice->getProperties().deviceName);
    }

    for (const auto& layer : instance.getLayerProperties()) {
        ui->listWidgetLayers->addItem(layer.layerName);
    }

    for (const auto& extension : instance.getExtensionProperties()) {
        ui->listWidgetExtensions->addItem(extension.extensionName);
    }
}

VulkanTab::~VulkanTab() {
    delete ui;
}

void VulkanTab::setDebugSettings(const QJsonObject& settings) {
    // Device
    ui->comboBoxDevice->setCurrentIndex(settings["device"].toInt());

    // Debug report
    ui->groupBoxDebugReport->setChecked(settings["debugReport"].toObject()["use"].toBool());
    ui->checkBoxInformation->setChecked(settings["debugReport"].toObject()["information"].toBool());
    ui->checkBoxWarning->setChecked(settings["debugReport"].toObject()["warning"].toBool());
    ui->checkBoxPerformance->setChecked(settings["debugReport"].toObject()["performance"].toBool());
    ui->checkBoxError->setChecked(settings["debugReport"].toObject()["error"].toBool());
    ui->checkBoxDebug->setChecked(settings["debugReport"].toObject()["debug"].toBool());

    // Layers
    ui->groupBoxLayers->setChecked(settings["layers"].toObject()["use"].toBool());
    for (const auto& layer : settings["layers"].toObject()["list"].toArray()) {
        QList<QListWidgetItem*> items = ui->listWidgetLayers->findItems(layer.toString(), Qt::MatchFixedString);
        if (items.length()) {
            ui->listWidgetLayers->setCurrentItem(items.at(0), QItemSelectionModel::Select);
        }
    }

    // Extensions
    ui->groupBoxExtensions->setChecked(settings["extensions"].toObject()["use"].toBool());
    for (const auto& extension : settings["extensions"].toObject()["list"].toArray()) {
        QList<QListWidgetItem*> items = ui->listWidgetExtensions->findItems(extension.toString(), Qt::MatchFixedString);
        if (items.length()) {
            ui->listWidgetExtensions->setCurrentItem(items.at(0), QItemSelectionModel::Select);
        }
    }
}

QJsonObject VulkanTab::debugSettings() const {
    QJsonObject obj;

    // Device
    obj["device"] = QJsonValue(ui->comboBoxDevice->currentIndex());

    // Debug report
    QJsonObject debugReportObj;
    debugReportObj["use"] = QJsonValue(ui->groupBoxDebugReport->isChecked());
    debugReportObj["information"] = QJsonValue(ui->checkBoxInformation->isChecked());
    debugReportObj["warning"] = QJsonValue(ui->checkBoxWarning->isChecked());
    debugReportObj["performance"] = QJsonValue(ui->checkBoxPerformance->isChecked());
    debugReportObj["error"] = QJsonValue(ui->checkBoxError->isChecked());
    debugReportObj["debug"] = QJsonValue(ui->checkBoxDebug->isChecked());
    obj["debugReport"] = debugReportObj;

    // Layers
    QJsonObject layersObj;
    layersObj["use"] = QJsonValue(ui->groupBoxLayers->isChecked());
    QJsonArray layersList;

    for (const auto& item : ui->listWidgetLayers->selectedItems()) {
        layersList.append(item->text());
    }

    layersObj["list"] = layersList;

    obj["layers"] = layersObj;

    // Extensions
    QJsonObject extensionsObj;
    extensionsObj["use"] = QJsonValue(ui->groupBoxExtensions->isChecked());

    QJsonArray extensionsList;

    for (const auto& item : ui->listWidgetExtensions->selectedItems()) {
        extensionsList.append(item->text());
    }

    extensionsObj["list"] = extensionsList;

    obj["extensions"] = extensionsObj;

    return obj;
}

QString VulkanTab::name() const {
    return "vulkan";
}

void VulkanTab::on_comboBoxDevice_currentIndexChanged(int currentIndex) {
    Q_UNUSED(currentIndex)
    emit flush();
}

} // DebugSettingsEditor

} // Origin
