#include "settingsframe.h"
#include "ui_settingsframe.h"

SettingsFrame::SettingsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsFrame)
{
    ui->setupUi(this);
    this->addedGPUInfo = false;
    this->initMonitorValues();
    connect(this->ui->addGraphBtn, SIGNAL(clicked()), this, SLOT(handleAddGraphBtnClicked()));

    this->refreshMSLineEdit = new IntRangeLineEdit(this, IntRangeLineEditFocusType::Out, "refresh",
                                                   2000, 2000, 20000);
    this->xAxisTicksLineEdit = new IntRangeLineEdit(this, IntRangeLineEditFocusType::Out, "xaxis",
                                                    10, 5, 25);
    this->ui->diagramConfigFormLayout->addRow(new QLabel(tr("Refresh")), this->refreshMSLineEdit);
    this->ui->diagramConfigFormLayout->addRow(new QLabel(tr("X-Ticks")), this->xAxisTicksLineEdit);

    connect(this->refreshMSLineEdit, SIGNAL(focussed(IntRangeLineEdit*,bool,int)), this,
            SLOT(handleRefreshLineEditFocusOut(IntRangeLineEdit*,bool,int)));

    connect(this->xAxisTicksLineEdit, SIGNAL(focussed(IntRangeLineEdit*,bool,int)), this,
            SLOT(handleRefreshLineEditFocusOut(IntRangeLineEdit*,bool,int)));
}

SettingsFrame::~SettingsFrame()
{
    delete this->refreshMSLineEdit;
    delete this->xAxisTicksLineEdit;
    delete this->ui;
    delete this->monitorValuesModel;
}

QStandardItem *SettingsFrame::getSelectedMonitorValue()
{
    return this->monitorValuesModel->itemFromIndex(
        this->ui->monitorValuesListView->selectionModel()->currentIndex());
}

int SettingsFrame::getXAxisTicks()
{
    return this->xAxisTicksLineEdit->getIntValue();
}

unsigned long SettingsFrame::getRefreshMS()
{
    return static_cast<unsigned long>(this->refreshMSLineEdit->getLongValue());
}

void SettingsFrame::readAllGPUValues(GPUStatsModel *m, NVidiaGPU *gpu)
{
    QMap<int, QStringList> *mm = m->vals;
    mm->insert(0,
               QStringList({tr("Total Memory"),
                            GPUHelpers::readGPUValue(gpu->index, "memory.total")}));
    mm->insert(1,
               QStringList({tr("Max. GPU Clock"),
                            GPUHelpers::readGPUValue(gpu->index, "clocks.max.graphics")}));

    mm->insert(2,
               QStringList({tr("Max. RAM Clock"),
                            GPUHelpers::readGPUValue(gpu->index, "clocks.max.memory")}));
    emit m->dataChanged(
        m->index(0, 0),
        m->index(m->rowCount(), m->columnCount()));

    emit m->layoutChanged();

// emit dataChanged(index(0, 0),
// index(rowCount(), columnCount()));
// emit layoutChanged();
}

void SettingsFrame::handleAddGraphBtnClicked()
{
    emit addMonitorBtnClicked();
}

void SettingsFrame::handleSelectionChanged(QItemSelection sel1, QItemSelection sel2)
{
    GPUStatsModel *m2 = static_cast<GPUStatsModel *>(this->ui->gpuStatsTable->model());
    this->readAllGPUValues(m2, smi->gpus->at(0));
    emit gpuListSelectionChanged(sel1);
}

void SettingsFrame::handleRefreshLineEditFocusOut(IntRangeLineEdit *le, bool hasFocus, int value)
{
    if (!le->hasAcceptableInput()) {
        QMessageBox::warning(this, tr("Invalid number"),
                             le->getValidationError(), QMessageBox::Ok);
        le->setText(QString::number(le->getLastValue()));
    } else {
        le->setNewValue(value);
    }
}

void SettingsFrame::initMonitorValues()
{
    this->monitorValuesModel = new QStandardItemModel();

    QStandardItem *qsi = new QStandardItem(tr("Fan: Speed"));
    qsi->setData(QVariant("fan.speed"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem(tr("GPU: Temperature"));
    qsi->setData(QVariant("temperature.gpu"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem(tr("Memory: Temperature"));
    qsi->setData(QVariant("temperature.memory"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem(tr("Memory: Used"));
    qsi->setData(QVariant("memory.used"), Qt::UserRole);
    this->monitorValuesModel->appendRow(qsi);

    qsi = new QStandardItem(tr("Power: Last value"));
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
