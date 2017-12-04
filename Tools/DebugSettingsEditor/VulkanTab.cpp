#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include <QJsonObject>

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
    return QJsonObject();
}

QString VulkanTab::name() const {
    return "vulkan";
}
