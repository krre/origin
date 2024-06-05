#pragma once
#include "AbstractTab.h"

class QCheckBox;
class QComboBox;

class GeneralTab : public AbstractTab {
    Q_OBJECT
public:
    GeneralTab();

    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject debugSettings() const override;

    QString name() const override;

private:
    QCheckBox* m_enableCheckBox = nullptr;
    QCheckBox* m_debugHudCheckBox = nullptr;

    QComboBox* m_screenComboBox = nullptr;
    QComboBox* m_saveComboBox = nullptr;
    QComboBox* m_rendererComboBox = nullptr;
};
