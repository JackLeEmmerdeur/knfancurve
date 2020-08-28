#include "settingsframe.h"
#include "ui_settingsframe.h"

SettingsFrame::SettingsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsFrame)
{
    this->addedGPUInfo = false;
    ui->setupUi(this);
}

SettingsFrame::~SettingsFrame()
{
    delete ui;
}

void SettingsFrame::addGPUInfo(NVidiaSMI *smi)
{
    if (this->addedGPUInfo == false && smi->gpuCount() > 0) {
        QListView *v = this->ui->gpuListView;
        QStandardItemModel *m = new QStandardItemModel(v);
        for (NVidiaGPU *q: *smi->gpus)
            m->appendRow(new QStandardItem(q->name));
        v->setModel(m);
        this->addedGPUInfo = true;
    }
}
