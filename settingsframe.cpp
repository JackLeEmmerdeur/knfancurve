#include "settingsframe.h"
#include "ui_settingsframe.h"

SettingsFrame::SettingsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsFrame)
{
    ui->setupUi(this);
}

SettingsFrame::~SettingsFrame()
{
    delete ui;
}

void SettingsFrame::addDebugInfo(const QString &info)
{
    this->ui->textEdit->setText(info);
}
