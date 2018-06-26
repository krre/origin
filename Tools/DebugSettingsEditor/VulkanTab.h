#pragma once
#include "AbstractTab.h"

namespace Ui {
    class VulkanTab;
}

namespace DebugSettingsEditor {

class VulkanTab : public AbstractTab {
    Q_OBJECT

public:
    explicit VulkanTab();
    ~VulkanTab();
    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject debugSettings() const override;
    QString name() const;

private slots:
    void on_comboBoxDevice_currentIndexChanged(int currentIndex);
    void on_pushButtonSelectAll_clicked();
    void on_pushButtonUnselectAll_clicked();

private:
    void changeStateDebugReportCheckBoxes(bool checked);

    Ui::VulkanTab* ui;
};

} // DebugSettingsEditor
