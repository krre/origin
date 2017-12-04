#pragma once
#include "AbstractTab.h"

namespace Ui {
    class GeneralTab;
}

class GeneralTab : public AbstractTab {
    Q_OBJECT

public:
    explicit GeneralTab();
    ~GeneralTab();
    void setDebugSettings(const QJsonObject& settings) override;
    QJsonObject debugSettings() const override;
    QString name() const;

private:
    Ui::GeneralTab* ui;
};
