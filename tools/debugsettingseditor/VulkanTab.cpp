#include "VulkanTab.h"
#include "SelectButtonRow.h"
#include "ListBox.h"
#include "vulkan/api/Instance.h"
#include "vulkan/api/device/PhysicalDevices.h"
#include "vulkan/api/device/PhysicalDevice.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QtWidgets>

VulkanTab::VulkanTab() {
    deviceComboBox = new QComboBox;
    connect(deviceComboBox, &QComboBox::currentIndexChanged, this, &VulkanTab::flush);

    debugReportGroupBox = new QGroupBox(tr("Debug report"));
    debugReportGroupBox->setCheckable(true);
    connect(debugReportGroupBox, &QGroupBox::toggled, this, &VulkanTab::flush);

    infoCheckBox = new QCheckBox(tr("Information"));
    connect(infoCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    warnCheckBox = new QCheckBox(tr("Warning"));
    connect(warnCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    perfCheckBox = new QCheckBox(tr("Performance"));
    connect(perfCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    errorCheckBox = new QCheckBox(tr("Error"));
    connect(errorCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    debugCheckBox = new QCheckBox(tr("Debug"));
    connect(debugCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    auto selectButtonRow = new SelectButtonRow;
    connect(selectButtonRow, &SelectButtonRow::select, this, &VulkanTab::debugReportSelectAll);
    connect(selectButtonRow, &SelectButtonRow::unselect, this, &VulkanTab::debugReportUnselectAll);
    connect(selectButtonRow, &SelectButtonRow::reset, this, &VulkanTab::debugReportReset);

    auto debugLayout = new QGridLayout;
    debugLayout->addWidget(infoCheckBox, 0, 0);
    debugLayout->addWidget(perfCheckBox, 0, 1);
    debugLayout->addWidget(debugCheckBox, 0, 2);
    debugLayout->addWidget(warnCheckBox, 1, 0);
    debugLayout->addWidget(errorCheckBox, 1, 1);
    debugLayout->addLayout(selectButtonRow, 2, 0, 2, 0);

    debugLayout->setColumnStretch(2, 1);

    debugReportGroupBox->setLayout(debugLayout);

    auto deviceLayout = new QHBoxLayout;
    deviceLayout->addWidget(new QLabel(tr("Graphics device:")));
    deviceLayout->addWidget(deviceComboBox);
    deviceLayout->addStretch();

    QStringList extensions = { "VK_EXT_debug_report", "VK_KHR_surface" };

#if defined(Q_OS_WIN)
    extensions << "VK_KHR_win32_surface";
#elif defined(Q_OS_UNIX)
    extensions << "VK_KHR_xcb_surface";
#endif

    extensionsListBox = new ListBox(tr("Extensions"), extensions);
    connect(extensionsListBox, &QGroupBox::toggled, this, &VulkanTab::flush);
    connect(extensionsListBox, &ListBox::flush, this, &VulkanTab::flush);

    layersListBox = new ListBox(tr("Layers"), { "VK_LAYER_LUNARG_core_validation", "VK_LAYER_LUNARG_parameter_validation", "VK_LAYER_LUNARG_standard_validation" });
    connect(layersListBox, &QGroupBox::toggled, this, &VulkanTab::flush);
    connect(layersListBox, &ListBox::flush, this, &VulkanTab::flush);

    auto listBoxLayout = new QHBoxLayout;
    listBoxLayout->addWidget(extensionsListBox);
    listBoxLayout->addWidget(layersListBox);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addLayout(deviceLayout);
    verticalLayout->addWidget(debugReportGroupBox);
    verticalLayout->addLayout(listBoxLayout);
    verticalLayout->addStretch();

    setLayout(verticalLayout);

    Vulkan::Instance instance;
    instance.create();

    Vulkan::PhysicalDevices physicalDevices(&instance);

    for (size_t i = 0; i < physicalDevices.count(); i++) {
        Vulkan::PhysicalDevice* physicalDevice = physicalDevices.physicalDevice(i);
        deviceComboBox->insertItem(i, physicalDevice->properties().deviceName);
    }

    for (const auto& layer : instance.layerProperties()) {
        layersListBox->addValue(layer.layerName);
    }

    for (const auto& extension : instance.extensionProperties()) {
        extensionsListBox->addValue(extension.extensionName);
    }
}

void VulkanTab::setDebugSettings(const QJsonObject& settings) {
    // Device
    deviceComboBox->setCurrentIndex(settings["device"].toInt());

    // Debug report
    debugReportGroupBox->setChecked(settings["debugReport"].toObject()["use"].toBool());
    infoCheckBox->setChecked(settings["debugReport"].toObject()["information"].toBool());
    warnCheckBox->setChecked(settings["debugReport"].toObject()["warning"].toBool());
    perfCheckBox->setChecked(settings["debugReport"].toObject()["performance"].toBool());
    errorCheckBox->setChecked(settings["debugReport"].toObject()["error"].toBool());
    debugCheckBox->setChecked(settings["debugReport"].toObject()["debug"].toBool());

    // Layers
    layersListBox->setChecked(settings["layers"].toObject()["use"].toBool());

    QStringList layersSelection;

    for (const auto& layer : settings["layers"].toObject()["list"].toArray()) {
        layersSelection.append(layer.toString());
    }

    layersListBox->setSelection(layersSelection);

    // Extensions
    extensionsListBox->setChecked(settings["extensions"].toObject()["use"].toBool());

    QStringList extensionsSelection;

    for (const auto& extension : settings["extensions"].toObject()["list"].toArray()) {
        extensionsSelection.append(extension.toString());
    }

    extensionsListBox->setSelection(extensionsSelection);
}

QJsonObject VulkanTab::debugSettings() const {
    QJsonObject obj;

    // Device
    obj["device"] = QJsonValue(deviceComboBox->currentIndex());

    // Debug report
    QJsonObject debugReportObj;
    debugReportObj["use"] = QJsonValue(debugReportGroupBox->isChecked());
    debugReportObj["information"] = QJsonValue(infoCheckBox->isChecked());
    debugReportObj["warning"] = QJsonValue(warnCheckBox->isChecked());
    debugReportObj["performance"] = QJsonValue(perfCheckBox->isChecked());
    debugReportObj["error"] = QJsonValue(errorCheckBox->isChecked());
    debugReportObj["debug"] = QJsonValue(debugCheckBox->isChecked());
    obj["debugReport"] = debugReportObj;

    // Layers
    QJsonObject layersObj;
    layersObj["use"] = QJsonValue(layersListBox->isChecked());
    layersObj["list"] = QJsonArray::fromStringList(layersListBox->selection());

    obj["layers"] = layersObj;

    // Extensions
    QJsonObject extensionsObj;
    extensionsObj["use"] = QJsonValue(extensionsListBox->isChecked());
    extensionsObj["list"] = QJsonArray::fromStringList(extensionsListBox->selection());;

    obj["extensions"] = extensionsObj;

    return obj;
}

void VulkanTab::setDefaultSettings() {
    debugReportReset();
    extensionsListBox->reset();
    layersListBox->reset();
}

QString VulkanTab::name() const {
    return "vulkan";
}

void VulkanTab::debugReportSelectAll() {
    changeStateDebugReportCheckBoxes(true);
}

void VulkanTab::debugReportUnselectAll() {
    changeStateDebugReportCheckBoxes(false);
}

void VulkanTab::debugReportReset() {
    changeStateDebugReportCheckBoxes(false);
    warnCheckBox->setChecked(true);
    errorCheckBox->setChecked(true);
    emit flush();
}

void VulkanTab::changeStateDebugReportCheckBoxes(bool checked) {
    infoCheckBox->setChecked(checked);
    warnCheckBox->setChecked(checked);
    perfCheckBox->setChecked(checked);
    errorCheckBox->setChecked(checked);
    debugCheckBox->setChecked(checked);
    emit flush();
}
