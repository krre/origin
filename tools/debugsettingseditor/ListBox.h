#pragma once
#include <QGroupBox>

class QListWidget;

class ListBox : public QGroupBox {
    Q_OBJECT
public:
    ListBox(const QString& title, const QStringList& defaultSelection = QStringList());

    void addValue(const QString& value);

    void setSelection(const QStringList& selection);
    QStringList selection() const;

signals:
    void flush();

public slots:
    void reset();

private slots:
    void selectAll();
    void unselectAll();

private:
    QListWidget* listWidget = nullptr;
    QStringList defaultSelection;
};
