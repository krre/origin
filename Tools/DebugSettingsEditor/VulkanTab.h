#pragma once
#include <QWidget>

namespace Ui {
    class VulkanTab;
}

class VulkanTab : public QWidget {
    Q_OBJECT

public:
    explicit VulkanTab();
    ~VulkanTab();

private:
    Ui::VulkanTab* ui;
};
