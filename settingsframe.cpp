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

void SettingsFrame::addDebugInfo(NVidiaSMI *smi)
{
    this->ui->textEdit->setText(smi->gpu(0)->id);
}
