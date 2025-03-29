#include "GeneralTab.h"
#include <QJsonObject>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QDir>

GeneralTab::GeneralTab() {
    m_enableCheckBox = new QCheckBox(tr("Use debug settings"));
    connect(m_enableCheckBox, &QCheckBox::toggled, this, &GeneralTab::flush);

    m_debugHudCheckBox = new QCheckBox(tr("Show debug HUD"));
    connect(m_debugHudCheckBox, &QCheckBox::toggled, this, &GeneralTab::flush);

    m_screenComboBox = new QComboBox;
    m_screenComboBox->addItems({ tr("Menu"), tr("Settings"), tr("Game"), tr("New Game"), tr("Load Game"), tr("Wait") });

    m_saveComboBox = new QComboBox;

    QDir dir(QDir::currentPath() + "/Saves");

    for (const QString& name : dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        m_saveComboBox->addItem(name);
    }

    m_rendererComboBox = new QComboBox;
    m_rendererComboBox->addItems({ tr("Polygonal"), tr("Raycast") });

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Default screen:"), m_screenComboBox);
    formLayout->addRow(tr("Save:"), m_saveComboBox);
    formLayout->addRow(tr("Renderer:"), m_rendererComboBox);

    formLayout->itemAt(formLayout->indexOf(m_screenComboBox))->setAlignment(Qt::AlignLeft);
    formLayout->itemAt(formLayout->indexOf(m_saveComboBox))->setAlignment(Qt::AlignLeft);
    formLayout->itemAt(formLayout->indexOf(m_rendererComboBox))->setAlignment(Qt::AlignLeft);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_enableCheckBox);
    verticalLayout->addWidget(m_debugHudCheckBox);
    verticalLayout->addLayout(formLayout);
    verticalLayout->addStretch();

    setLayout(verticalLayout);
}

void GeneralTab::setDebugSettings(const QJsonObject& settings) {
    m_enableCheckBox->setChecked(settings["enable"].toBool());
    m_debugHudCheckBox->setChecked(settings["debugHud"].toBool());
    m_screenComboBox->setCurrentIndex(settings["screen"].toInt());
    m_saveComboBox->setCurrentText(settings["save"].toString());
    m_rendererComboBox->setCurrentIndex(settings["renderer"].toInt());
}

QJsonObject GeneralTab::debugSettings() const {
    QJsonObject obj;
    obj["enable"] = QJsonValue(m_enableCheckBox->isChecked());
    obj["debugHud"] = QJsonValue(m_debugHudCheckBox->isChecked());
    obj["screen"] = m_screenComboBox->currentIndex();
    obj["save"] = QJsonValue(m_saveComboBox->currentText());
    obj["renderer"] = QJsonValue(m_rendererComboBox->currentIndex());

    return obj;
}

QString GeneralTab::name() const {
    return "general";
}
