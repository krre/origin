#pragma once
#include <QUndoCommand>

class DeleteCommand : public QUndoCommand {

public:
    explicit DeleteCommand(QUndoCommand* parent = 0);

signals:

public slots:
};

class AddCommand : public QUndoCommand {

public:
    explicit AddCommand(QUndoCommand* parent = 0);

signals:

public slots:
};
