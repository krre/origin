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
    m_deviceComboBox = new QComboBox;
    connect(m_deviceComboBox, &QComboBox::currentIndexChanged, this, &VulkanTab::flush);

    m_debugReportGroupBox = new QGroupBox(tr("Debug report"));
    m_debugReportGroupBox->setCheckable(true);
    connect(m_debugReportGroupBox, &QGroupBox::toggled, this, &VulkanTab::flush);

    m_infoCheckBox = new QCheckBox(tr("Information"));
    connect(m_infoCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    m_warnCheckBox = new QCheckBox(tr("Warning"));
    connect(m_warnCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    m_perfCheckBox = new QCheckBox(tr("Performance"));
    connect(m_perfCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    m_errorCheckBox = new QCheckBox(tr("Error"));
    connect(m_errorCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    m_debugCheckBox = new QCheckBox(tr("Debug"));
    connect(m_debugCheckBox, &QCheckBox::toggled, this, &VulkanTab::flush);

    auto selectButtonRow = new SelectButtonRow;
    connect(selectButtonRow, &SelectButtonRow::select, this, &VulkanTab::debugReportSelectAll);
    connect(selectButtonRow, &SelectButtonRow::unselect, this, &VulkanTab::debugReportUnselectAll);
    connect(selectButtonRow, &SelectButtonRow::reset, this, &VulkanTab::debugReportReset);

    auto debugLayout = new QGridLayout;
    debugLayout->addWidget(m_infoCheckBox, 0, 0);
    debugLayout->addWidget(m_perfCheckBox, 0, 1);
    debugLayout->addWidget(m_debugCheckBox, 0, 2);
    debugLayout->addWidget(m_warnCheckBox, 1, 0);
    debugLayout->addWidget(m_errorCheckBox, 1, 1);
    debugLayout->addLayout(selectButtonRow, 2, 0, 2, 0);

    debugLayout->setColumnStretch(2, 1);

    m_debugReportGroupBox->setLayout(debugLayout);

    auto deviceLayout = new QHBoxLayout;
    deviceLayout->addWidget(new QLabel(tr("Graphics device:")));
    deviceLayout->addWidget(m_deviceComboBox);
    deviceLayout->addStretch();

    QStringList extensions = { "VK_EXT_debug_report", "VK_KHR_surface" };

#if defined(Q_OS_WIN)
    extensions << "VK_KHR_win32_surface";
#elif defined(Q_OS_UNIX)
    extensions << "VK_KHR_xcb_surface";
#endif

    m_extensionsListBox = new ListBox(tr("Extensions"), extensions);
    connect(m_extensionsListBox, &QGroupBox::toggled, this, &VulkanTab::flush);
    connect(m_extensionsListBox, &ListBox::flush, this, &VulkanTab::flush);

    m_layersListBox = new ListBox(tr("Layers"), { "VK_LAYER_LUNARG_core_validation", "VK_LAYER_LUNARG_parameter_validation", "VK_LAYER_LUNARG_standard_validation" });
    connect(m_layersListBox, &QGroupBox::toggled, this, &VulkanTab::flush);
    connect(m_layersListBox, &ListBox::flush, this, &VulkanTab::flush);

    auto listBoxLayout = new QHBoxLayout;
    listBoxLayout->addWidget(m_extensionsListBox);
    listBoxLayout->addWidget(m_layersListBox);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addLayout(deviceLayout);
    verticalLayout->addWidget(m_debugReportGroupBox);
    verticalLayout->addLayout(listBoxLayout);
    verticalLayout->addStretch();

    setLayout(verticalLayout);

    Vulkan::Instance instance;
    instance.create();

    Vulkan::PhysicalDevices physicalDevices(&instance);

    for (size_t i = 0; i < physicalDevices.count(); i++) {
        Vulkan::PhysicalDevice* physicalDevice = physicalDevices.physicalDevice(i);
        m_deviceComboBox->insertItem(i, physicalDevice->properties().deviceName);
    }

    for (const auto& layer : instance.layerProperties()) {
        m_layersListBox->addValue(layer.layerName);
    }

    for (const auto& extension : instance.extensionProperties()) {
        m_extensionsListBox->addValue(extension.extensionName);
    }
}

void VulkanTab::setDebugSettings(const QJsonObject& settings) {
    // Device
    m_deviceComboBox->setCurrentIndex(settings["device"].toInt());

    // Debug report
    m_debugReportGroupBox->setChecked(settings["debugReport"].toObject()["use"].toBool());
    m_infoCheckBox->setChecked(settings["debugReport"].toObject()["information"].toBool());
    m_warnCheckBox->setChecked(settings["debugReport"].toObject()["warning"].toBool());
    m_perfCheckBox->setChecked(settings["debugReport"].toObject()["performance"].toBool());
    m_errorCheckBox->setChecked(settings["debugReport"].toObject()["error"].toBool());
    m_debugCheckBox->setChecked(settings["debugReport"].toObject()["debug"].toBool());

    // Layers
    m_layersListBox->setChecked(settings["layers"].toObject()["use"].toBool());

    QStringList layersSelection;

    for (const auto& layer : settings["layers"].toObject()["list"].toArray()) {
        layersSelection.append(layer.toString());
    }

    m_layersListBox->setSelection(layersSelection);

    // Extensions
    m_extensionsListBox->setChecked(settings["extensions"].toObject()["use"].toBool());

    QStringList extensionsSelection;

    for (const auto& extension : settings["extensions"].toObject()["list"].toArray()) {
        extensionsSelection.append(extension.toString());
    }

    m_extensionsListBox->setSelection(extensionsSelection);
}

QJsonObject VulkanTab::debugSettings() const {
    QJsonObject obj;

    // Device
    obj["device"] = QJsonValue(m_deviceComboBox->currentIndex());

    // Debug report
    QJsonObject debugReportObj;
    debugReportObj["use"] = QJsonValue(m_debugReportGroupBox->isChecked());
    debugReportObj["information"] = QJsonValue(m_infoCheckBox->isChecked());
    debugReportObj["warning"] = QJsonValue(m_warnCheckBox->isChecked());
    debugReportObj["performance"] = QJsonValue(m_perfCheckBox->isChecked());
    debugReportObj["error"] = QJsonValue(m_errorCheckBox->isChecked());
    debugReportObj["debug"] = QJsonValue(m_debugCheckBox->isChecked());
    obj["debugReport"] = debugReportObj;

    // Layers
    QJsonObject layersObj;
    layersObj["use"] = QJsonValue(m_layersListBox->isChecked());
    layersObj["list"] = QJsonArray::fromStringList(m_layersListBox->selection());

    obj["layers"] = layersObj;

    // Extensions
    QJsonObject extensionsObj;
    extensionsObj["use"] = QJsonValue(m_extensionsListBox->isChecked());
    extensionsObj["list"] = QJsonArray::fromStringList(m_extensionsListBox->selection());;

    obj["extensions"] = extensionsObj;

    return obj;
}

void VulkanTab::setDefaultSettings() {
    debugReportReset();
    m_extensionsListBox->reset();
    m_layersListBox->reset();
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
    m_warnCheckBox->setChecked(true);
    m_errorCheckBox->setChecked(true);
    emit flush();
}

void VulkanTab::changeStateDebugReportCheckBoxes(bool checked) {
    m_infoCheckBox->setChecked(checked);
    m_warnCheckBox->setChecked(checked);
    m_perfCheckBox->setChecked(checked);
    m_errorCheckBox->setChecked(checked);
    m_debugCheckBox->setChecked(checked);
    emit flush();
}
