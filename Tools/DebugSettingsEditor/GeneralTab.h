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
    void setJsonSettings(const QJsonObject& settings) override;
    QJsonObject jsonSettings() const override;
    QString name() const;

private:
    Ui::GeneralTab* ui;
};
