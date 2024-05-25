#pragma once
#include "AbstractTab.h"

namespace Ui {
    class VulkanTab;
}

class QListWidget;

namespace DebugSettingsEditor {

class VulkanTab : public AbstractTab {
    Q_OBJECT

public:
    explicit VulkanTab();
    ~VulkanTab();

    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject debugSettings() const override;
    void setDefaultSettings() override;

    QString name() const;

private slots:
    void on_comboBoxDevice_currentIndexChanged(int currentIndex);

    void on_pushButtonDebugReportSelectAll_clicked();
    void on_pushButtonDebugReportUnselectAll_clicked();
    void on_pushButtonDebugReportReset_clicked();

    void on_pushButtonExtensionsSelectAll_clicked();
    void on_pushButtonExtensionsUnselectAll_clicked();
    void on_pushButtonExtensionsReset_clicked();

    void on_pushButtonLayersSelectAll_clicked();
    void on_pushButtonLayersUnselectAll_clicked();
    void on_pushButtonLayersReset_clicked();

private:
    void changeStateDebugReportCheckBoxes(bool checked);
    void selectListWidgetItems(QListWidget* listWidget, const QStringList& list);

    Ui::VulkanTab* ui;
};

} // DebugSettingsEditor
