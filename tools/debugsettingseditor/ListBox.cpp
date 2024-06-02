#include "ListBox.h"
#include "SelectButtonRow.h"
#include <QListWidget>

ListBox::ListBox(const QString& title, const QStringList& defaultSelection) : QGroupBox(title), defaultSelection(defaultSelection) {
    setCheckable(true);

    listWidget = new QListWidget;
    listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(listWidget, &QListWidget::itemSelectionChanged, this, &ListBox::flush);

    auto selectButtonRow = new SelectButtonRow;
    connect(selectButtonRow, &SelectButtonRow::select, this, &ListBox::selectAll);
    connect(selectButtonRow, &SelectButtonRow::unselect, this, &ListBox::unselectAll);
    connect(selectButtonRow, &SelectButtonRow::reset, this, &ListBox::reset);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(listWidget);
    verticalLayout->addLayout(selectButtonRow);

    setLayout(verticalLayout);
}

void ListBox::addValue(const QString& value) {
    listWidget->addItem(value);
}

void ListBox::setSelection(const QStringList& selection) {
    for (const auto& value : selection) {
        QList<QListWidgetItem*> items = listWidget->findItems(value, Qt::MatchFixedString);

        if (items.length()) {
            listWidget->setCurrentItem(items.at(0), QItemSelectionModel::Select);
        }
    }
}

QStringList ListBox::selection() const {
    QStringList result;

    for (const auto& item : listWidget->selectedItems()) {
        result.append(item->text());
    }

    return result;
}

void ListBox::selectAll() {
    listWidget->selectAll();
    emit flush();
}

void ListBox::unselectAll() {
    listWidget->clearSelection();
    emit flush();
}

void ListBox::reset() {
    listWidget->clearSelection();

    for (int i = 0; i < listWidget->count(); i++) {
        if (defaultSelection.contains(listWidget->item(i)->text())) {
            listWidget->setCurrentItem(listWidget->item(i), QItemSelectionModel::Select);
        }
    }

    emit flush();
}
