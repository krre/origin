#pragma once
#include "AbstractTab.h"

namespace Ui {
    class VulkanTab;
}

namespace Origin {

namespace DebugSettingsEditor {

class VulkanTab : public AbstractTab {
    Q_OBJECT

public:
    explicit VulkanTab();
    ~VulkanTab();
    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject debugSettings() const override;
    QString name() const;

private:
    Ui::VulkanTab* ui;
};

} // DebugSettingsEditor

} // Origin
