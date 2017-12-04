#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include <QJsonObject>
#include <QJsonValue>

VulkanTab::VulkanTab() :
        ui(new Ui::VulkanTab) {
    ui->setupUi(this);

    connect(ui->checkBoxLayersUse, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxLayersDump, &QCheckBox::toggled, this, &VulkanTab::flush);

    connect(ui->checkBoxExtensionsUse, &QCheckBox::toggled, this, &VulkanTab::flush);
    connect(ui->checkBoxExtensionsDump, &QCheckBox::toggled, this, &VulkanTab::flush);
}

VulkanTab::~VulkanTab() {
    delete ui;
}

void VulkanTab::setDebugSettings(const QJsonObject& settings) {

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
