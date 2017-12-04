#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include "Graphics/Vulkan/Instance.h"
#include <QJsonObject>
#include <QJsonValue>

VulkanTab::VulkanTab() :
        ui(new Ui::VulkanTab) {
    ui->setupUi(this);

    connect(ui->checkBoxLayersUse, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxLayersDump, &QCheckBox::toggled, this, &VulkanTab::flush);

    connect(ui->checkBoxExtensionsUse, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxExtensionsDump, &QCheckBox::toggled, this, &VulkanTab::flush);

    Vulkan::Instance instance;
    instance.create();

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
    ui->checkBoxLayersUse->setChecked(settings["layers"]["use"].toBool());
    ui->checkBoxLayersDump->setChecked(settings["layers"]["dump"].toBool());

    ui->checkBoxExtensionsUse->setChecked(settings["extensions"]["use"].toBool());
    ui->checkBoxExtensionsDump->setChecked(settings["extensions"]["dump"].toBool());
}

QJsonObject VulkanTab::debugSettings() const {
    QJsonObject layersObj;
    layersObj["use"] = QJsonValue(ui->checkBoxLayersUse->isChecked());
    layersObj["dump"] = QJsonValue(ui->checkBoxLayersDump->isChecked());

    QJsonObject extensionsObj;
    extensionsObj["use"] = QJsonValue(ui->checkBoxExtensionsUse->isChecked());
    extensionsObj["dump"] = QJsonValue(ui->checkBoxExtensionsDump->isChecked());

    QJsonObject obj;
    obj["layers"] = layersObj;
    obj["extensions"] = extensionsObj;

    return obj;
}

QString VulkanTab::name() const {
    return "vulkan";
}
