#include "ListBox.h"
#include "SelectButtonRow.h"
#include <QListWidget>

ListBox::ListBox(const QString& title, const QStringList& defaultSelection) : QGroupBox(title), m_defaultSelection(defaultSelection) {
    setCheckable(true);

    m_listWidget = new QListWidget;
    m_listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(m_listWidget, &QListWidget::itemSelectionChanged, this, &ListBox::flush);

    auto selectButtonRow = new SelectButtonRow;
    connect(selectButtonRow, &SelectButtonRow::select, this, &ListBox::selectAll);
    connect(selectButtonRow, &SelectButtonRow::unselect, this, &ListBox::unselectAll);
    connect(selectButtonRow, &SelectButtonRow::reset, this, &ListBox::reset);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_listWidget);
    verticalLayout->addLayout(selectButtonRow);

    setLayout(verticalLayout);
}

void ListBox::addValue(const QString& value) {
    m_listWidget->addItem(value);
}

void ListBox::setSelection(const QStringList& selection) {
    for (const auto& value : selection) {
        QList<QListWidgetItem*> items = m_listWidget->findItems(value, Qt::MatchFixedString);

        if (items.length()) {
            m_listWidget->setCurrentItem(items.at(0), QItemSelectionModel::Select);
        }
    }
}

QStringList ListBox::selection() const {
    QStringList result;

    for (const auto& item : m_listWidget->selectedItems()) {
        result.append(item->text());
    }

    return result;
}

void ListBox::selectAll() {
    m_listWidget->selectAll();
    emit flush();
}

void ListBox::unselectAll() {
    m_listWidget->clearSelection();
    emit flush();
}

void ListBox::reset() {
    m_listWidget->clearSelection();

    for (int i = 0; i < m_listWidget->count(); i++) {
        if (m_defaultSelection.contains(m_listWidget->item(i)->text())) {
            m_listWidget->setCurrentItem(m_listWidget->item(i), QItemSelectionModel::Select);
        }
    }

    emit flush();
}
