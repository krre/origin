#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

VulkanTab::VulkanTab() :
        ui(new Ui::VulkanTab) {
    ui->setupUi(this);

    connect(ui->groupBoxLayers, &QGroupBox::toggled, this, &VulkanTab::flush);
    connect(ui->groupBoxExtensions, &QGroupBox::toggled, this, &VulkanTab::flush);

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
    ui->groupBoxLayers->setChecked(settings["layers"].toObject()["use"].toBool());
    for (const auto& layer : settings["layers"].toObject()["list"].toArray()) {
        QList<QListWidgetItem*> items = ui->listWidgetLayers->findItems(layer.toString(), Qt::MatchFixedString);
        if (items.length()) {
            ui->listWidgetLayers->setCurrentItem(items.at(0), QItemSelectionModel::Select);
        }
    }

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
