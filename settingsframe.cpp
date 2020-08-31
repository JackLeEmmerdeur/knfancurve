#include "settingsframe.h"
#include "ui_settingsframe.h"

SettingsFrame::SettingsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsFrame)
{
    this->addedGPUInfo = false;
    ui->setupUi(this);
    this->initMonitorValues();
    connect(this->ui->addGraphBtn, SIGNAL(clicked()), this, SLOT(handleAddGraphBtnClicked()));
}

SettingsFrame::~SettingsFrame()
{
    delete this->ui;
    delete this->monitorValuesModel;
}

QStandardItem *SettingsFrame::getSelectedMonitorValue()
{
    return this->monitorValuesModel->itemFromIndex(
        this->ui->monitorValuesListView->selectionModel()->currentIndex());
}

void SettingsFrame::handleAddGraphBtnClicked()
{
    emit addMonitorBtnClicked();
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

    QStandardItem *qsi = new QStandardItem("Lüfter: Geschwindigkeit");
    qsi->setData(QVariant("fan.speed"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem("GPU: Temperatur");
    qsi->setData(QVariant("temperature.gpu"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem("Speicher: Temperatur");
    qsi->setData(QVariant("temperature.memory"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem("Speicher: Benutzt");
    qsi->setData(QVariant("memory.used"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem("Strom: Letzter Wert");
    qsi->setData(QVariant("power.draw"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    this->ui->monitorValuesListView->setModel(this->monitorValuesModel);
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
