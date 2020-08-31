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

#include "nvidiasmi.h"
#include "nvidiagpu.h"
#include "gpustatsmodel.h"

namespace Ui {
class SettingsFrame;
}

class SettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsFrame(QWidget *parent = nullptr);
    ~SettingsFrame();

    void readAllGPUInfo(NVidiaSMI *smi);
    void selectGPU(int index = 0);
    QStandardItem *getSelectedMonitorValue();

public slots:
    void handleSelectionChanged(QItemSelection sel1, QItemSelection sel2);
    void handleAddGraphBtnClicked();

signals:
    void gpuListSelectionChanged(QItemSelection sel);
    void addMonitorBtnClicked();

private:
    void initMonitorValues();
    Ui::SettingsFrame *ui;
    bool addedGPUInfo;
    NVidiaSMI *smi = nullptr;
    QStandardItemModel *monitorValuesModel;
};

#endif // SETTINGSFRAME_H
