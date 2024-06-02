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
    QCheckBox* enableCheckBox = nullptr;
    QCheckBox* debugHudCheckBox = nullptr;

    QComboBox* screenComboBox = nullptr;
    QComboBox* saveComboBox = nullptr;
    QComboBox* rendererComboBox = nullptr;
};
