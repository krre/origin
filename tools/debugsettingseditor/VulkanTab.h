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

    QComboBox* m_deviceComboBox = nullptr;
    QGroupBox* m_debugReportGroupBox = nullptr;

    QCheckBox* m_infoCheckBox = nullptr;
    QCheckBox* m_warnCheckBox = nullptr;
    QCheckBox* m_perfCheckBox = nullptr;
    QCheckBox* m_errorCheckBox = nullptr;
    QCheckBox* m_debugCheckBox = nullptr;

    ListBox* m_extensionsListBox = nullptr;
    ListBox* m_layersListBox = nullptr;
};
