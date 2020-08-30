#include "settingsframe.h"
#include "ui_settingsframe.h"

SettingsFrame::SettingsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsFrame)
{
    this->addedGPUInfo = false;
    ui->setupUi(this);

    this->initMonitorValues();
}

SettingsFrame::~SettingsFrame()
{
    delete this->ui;
    delete this->smi;
    delete this->monitorValuesModel;
}

void SettingsFrame::handleSelectionChanged(QItemSelection sel1, QItemSelection sel2)
{
    GPUStatsModel *m2 = static_cast<GPUStatsModel *>(this->ui->gpuStatsTable->model());

    m2->readAllGPUValues(smi->gpus->at(0));

    emit gpuListSelectionChanged(sel1);
}

void SettingsFrame::initMonitorValues()
{
    this->monitorValuesModel = new QStandardItemModel();
    this->monitorValuesModel->appendRow(new QStandardItem("fan.speed"));
    this->monitorValuesModel->appendRow(new QStandardItem("temperature.gpu"));
    this->monitorValuesModel->appendRow(new QStandardItem("temperature.memory"));
    this->monitorValuesModel->appendRow(new QStandardItem("memory.used"));
    this->monitorValuesModel->appendRow(new QStandardItem("power.draw"));
    this->ui->monitorValues->setModel(this->monitorValuesModel);
}

void SettingsFrame::selectGPU(int index)
{
    if (this->smi != nullptr && index < this->smi->getGPUCount()) {
        this->ui->gpuListView->selectionModel()->select(
            this->ui->gpuListView->model()->index(index, 0),
            QItemSelectionModel::Select
            );
    }
}

void SettingsFrame::readAllGPUInfo(NVidiaSMI *smi)
{
    if (this->addedGPUInfo == false && smi->getGPUCount() > 0) {
        this->smi = smi;
        QListView *v = this->ui->gpuListView;
        QStandardItemModel *m = new QStandardItemModel(v);
        for (NVidiaGPU *q: *smi->gpus)
            m->appendRow(new QStandardItem(q->name));
        v->setModel(m);
        this->addedGPUInfo = true;

        GPUStatsModel *m2 = new GPUStatsModel();
        this->ui->gpuStatsTable->setModel(m2);

        connect(this->ui->gpuListView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this,
                SLOT(handleSelectionChanged(QItemSelection,QItemSelection)));
    }
}
