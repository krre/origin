#pragma once
#include "AbstractTab.h"

class ListBox;

class QComboBox;
class QGroupBox;
class QCheckBox;
class QListWidget;

class VulkanTab : public AbstractTab {
    Q_OBJECT
public:
    VulkanTab();

    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject debugSettings() const override;
    void setDefaultSettings() override;

    QString name() const override;

private slots:
    void debugReportSelectAll();
    void debugReportUnselectAll();
    void debugReportReset();

private:
    void changeStateDebugReportCheckBoxes(bool checked);

    QComboBox* deviceComboBox = nullptr;
    QGroupBox* debugReportGroupBox = nullptr;

    QCheckBox* infoCheckBox = nullptr;
    QCheckBox* warnCheckBox = nullptr;
    QCheckBox* perfCheckBox = nullptr;
    QCheckBox* errorCheckBox = nullptr;
    QCheckBox* debugCheckBox = nullptr;

    ListBox* extensionsListBox = nullptr;
    ListBox* layersListBox = nullptr;
};
