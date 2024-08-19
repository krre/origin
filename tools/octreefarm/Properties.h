#pragma once
#include <QWidget>

class QUndoStack;
class QLabel;
class QPushButton;
class QCheckBox;

class OctreeEditor;
class Viewport;

class Properties : public QWidget {
    Q_OBJECT
public:
    Properties(OctreeEditor* octree, Viewport* viewport, QUndoStack* undoStack, QWidget* parent = nullptr);

    void setNodeLevel(int level);
    void setNodeIndex(int index);
    void setNodeColor(const QColor& color);

    void setShadeless(bool shadeless);
    bool shadeless() const;

private slots:
    void changeNodeColor();
    void onNodeSelected(int level, int index, const QColor& color);
    void onNodeDeselected();

    void levelPlus();
    void levelMinus();
    void levelReset();

private:
    void createUi();

    OctreeEditor* m_octree = nullptr;
    Viewport* m_viewport = nullptr;
    QUndoStack* m_undoStack = nullptr;
    QColor m_nodeColor;

    QLabel* m_levelLabel = nullptr;
    QLabel* m_indexLabel = nullptr;
    QPushButton* m_colorButton = nullptr;
    QCheckBox* m_shadelessCheckBox = nullptr;
};
