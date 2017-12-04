#include "VulkanTab.h"
#include "ui_VulkanTab.h"

VulkanTab::VulkanTab() :
        ui(new Ui::VulkanTab) {
    ui->setupUi(this);
}

VulkanTab::~VulkanTab() {
    delete ui;
}
