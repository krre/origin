#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include "Vulkan/API/Instance.h"
#include "Vulkan/API/Device/PhysicalDevices.h"
#include "Vulkan/API/Device/PhysicalDevice.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

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

    on_pushButtonDebugReportReset_clicked();
    on_pushButtonExtensionsReset_clicked();
    on_pushButtonLayersReset_clicked();
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

void VulkanTab::on_pushButtonDebugReportSelectAll_clicked() {
    changeStateDebugReportCheckBoxes(true);
}

void VulkanTab::on_pushButtonDebugReportUnselectAll_clicked() {
    changeStateDebugReportCheckBoxes(false);
}

void VulkanTab::on_pushButtonDebugReportReset_clicked() {
    changeStateDebugReportCheckBoxes(false);
    ui->checkBoxWarning->setChecked(true);
    ui->checkBoxError->setChecked(true);
    emit flush();
}

void VulkanTab::on_pushButtonExtensionsSelectAll_clicked() {
    ui->listWidgetExtensions->selectAll();
    emit flush();
}

void VulkanTab::on_pushButtonExtensionsUnselectAll_clicked() {
    ui->listWidgetExtensions->clearSelection();
    emit flush();
}

void VulkanTab::on_pushButtonExtensionsReset_clicked() {
    QStringList list;
    list << "VK_EXT_debug_report";
    list << "VK_KHR_surface";
    list << "VK_KHR_win32_surface";

    selectListWidgetItems(ui->listWidgetExtensions, list);
}

void VulkanTab::on_pushButtonLayersSelectAll_clicked() {
    ui->listWidgetLayers->selectAll();
    emit flush();
}

void VulkanTab::on_pushButtonLayersUnselectAll_clicked() {
    ui->listWidgetLayers->clearSelection();
    emit flush();
}

void VulkanTab::on_pushButtonLayersReset_clicked() {
    QStringList list;
    list << "VK_LAYER_LUNARG_core_validation";
    list << "VK_LAYER_LUNARG_parameter_validation";
    list << "VK_LAYER_LUNARG_standard_validation";

    selectListWidgetItems(ui->listWidgetLayers, list);
}

void VulkanTab::changeStateDebugReportCheckBoxes(bool checked) {
    ui->checkBoxInformation->setChecked(checked);
    ui->checkBoxWarning->setChecked(checked);
    ui->checkBoxPerformance->setChecked(checked);
    ui->checkBoxError->setChecked(checked);
    ui->checkBoxDebug->setChecked(checked);
    emit flush();
}

void VulkanTab::selectListWidgetItems(QListWidget* listWidget, const QStringList& list) {
    listWidget->clearSelection();

    for (int i = 0; i < listWidget->count(); i++) {
        if (list.contains(listWidget->item(i)->text())) {
            listWidget->setCurrentItem(listWidget->item(i), QItemSelectionModel::Select);
        }
    }

    emit flush();
}

} // DebugSettingsEditor
