#include "VulkanTab.h"
#include "ui_VulkanTab.h"
#include <QJsonObject>

VulkanTab::VulkanTab() :
        ui(new Ui::VulkanTab) {
    ui->setupUi(this);
}

VulkanTab::~VulkanTab() {
    delete ui;
}

void VulkanTab::setDebugSettings(const QJsonObject& settings) {

}

QJsonObject VulkanTab::jsonSettings() const {
    return QJsonObject();
}

QString VulkanTab::name() const {
    return "vulkan";
}
