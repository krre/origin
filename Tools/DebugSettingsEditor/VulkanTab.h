#pragma once
#include "AbstractTab.h"

namespace Ui {
    class VulkanTab;
}

class VulkanTab : public AbstractTab {
    Q_OBJECT

public:
    explicit VulkanTab();
    ~VulkanTab();
    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject jsonSettings() const override;
    QString name() const;

private:
    Ui::VulkanTab* ui;
};
