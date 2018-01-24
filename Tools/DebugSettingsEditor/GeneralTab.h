#pragma once
#include "AbstractTab.h"

namespace Ui {
    class GeneralTab;
}

namespace DebugSettingsEditor {

class GeneralTab : public AbstractTab {
    Q_OBJECT

public:
    explicit GeneralTab();
    ~GeneralTab();
    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject debugSettings() const override;
    QString name() const;

private slots:
    void on_comboBoxScreen_currentIndexChanged(int currentIndex);

private:
    Ui::GeneralTab* ui;
};

} // DebugSettingsEditor
