#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include "Graphics/Vulkan/Instance.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

VulkanTab::VulkanTab() :
        ui(new Ui::VulkanTab) {
    ui->setupUi(this);

    connect(ui->checkBoxLayersUse, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxLayersDump, &QCheckBox::toggled, this, &VulkanTab::flush);

    connect(ui->checkBoxExtensionsUse, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxExtensionsDump, &QCheckBox::toggled, this, &VulkanTab::flush);

    connect(ui->listWidgetLayers, &QListWidget::itemSelectionChanged, this, &VulkanTab::flush);
    connect(ui->listWidgetExtensions, &QListWidget::itemSelectionChanged, this, &VulkanTab::flush);

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
    for (const auto& layer : settings["layers"]["list"].toArray()) {
        QList<QListWidgetItem*> items = ui->listWidgetLayers->findItems(layer.toString(), Qt::MatchFixedString);
        if (items.length()) {
            ui->listWidgetLayers->setCurrentItem(items.at(0), QItemSelectionModel::Select);
        }
    }

    ui->checkBoxExtensionsUse->setChecked(settings["extensions"]["use"].toBool());
    ui->checkBoxExtensionsDump->setChecked(settings["extensions"]["dump"].toBool());
    for (const auto& extension : settings["extensions"]["list"].toArray()) {
        QList<QListWidgetItem*> items = ui->listWidgetExtensions->findItems(extension.toString(), Qt::MatchFixedString);
        if (items.length()) {
            ui->listWidgetExtensions->setCurrentItem(items.at(0), QItemSelectionModel::Select);
        }
    }
}

QJsonObject VulkanTab::debugSettings() const {
    QJsonObject obj;

    // Layers
    QJsonObject layersObj;
    layersObj["use"] = QJsonValue(ui->checkBoxLayersUse->isChecked());
    layersObj["dump"] = QJsonValue(ui->checkBoxLayersDump->isChecked());
    QJsonArray layersList;

    for (const auto& item : ui->listWidgetLayers->selectedItems()) {
        layersList.append(item->text());
    }

    layersObj["list"] = layersList;

    obj["layers"] = layersObj;

    // Extensions
    QJsonObject extensionsObj;
    extensionsObj["use"] = QJsonValue(ui->checkBoxExtensionsUse->isChecked());
    extensionsObj["dump"] = QJsonValue(ui->checkBoxExtensionsDump->isChecked());

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
