#pragma once
#include <QWidget>

class QJsonObject;

namespace DebugSettingsEditor {

class AbstractTab : public QWidget {
    Q_OBJECT

public:
    explicit AbstractTab() {}
    virtual void setDebugSettings(const QJsonObject& settings) = 0;
    virtual QJsonObject debugSettings() const = 0;
    virtual QString name() const = 0;

signals:
    void flush();
};

} // DebugSettingsEditor
