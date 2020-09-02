#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <typeinfo>
#include <QFrame>
#include <QListView>
#include <QItemSelectionModel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QItemSelection>
#include <QIntValidator>
#include <QLineEdit>
#include <QMessageBox>

#include "SMI.h"
#include "GPU.h"
#include "GPUStatsModel.h"
#include "IntRangeLineEdit.h"

namespace Ui {
class SettingsFrame;
}

class SettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsFrame(QWidget *parent = nullptr);
    ~SettingsFrame();

    void readAllGPUInfo(SMI *smi);
    void selectGPU(int index = 0);
    QStandardItem *getSelectedMonitorValue();
    int getXAxisTicks();
    unsigned long getRefreshMS();

public slots:
    void handleSelectionChanged(QItemSelection sel1, QItemSelection sel2);
    void handleAddGraphBtnClicked();
    void handleRefreshLineEditFocusOut(IntRangeLineEdit *le, bool hasFocus, int value);

signals:
    void gpuListSelectionChanged(QItemSelection sel);
    void addMonitorBtnClicked();

private:
    Ui::SettingsFrame *ui;
    bool addedGPUInfo;
    SMI *smi = nullptr;
    QStandardItemModel *monitorValuesModel;
    IntRangeLineEdit *refreshMSLineEdit;
    IntRangeLineEdit *xAxisTicksLineEdit;

    void readAllGPUValues(GPUStatsModel *m, GPU *gpu);
    void initMonitorValues();
};

#endif // SETTINGSFRAME_H
