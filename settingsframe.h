#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <typeinfo>
#include <QFrame>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include "nvidiasmi.h"
#include "nvidiagpu.h"

namespace Ui {
class SettingsFrame;
}

class SettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsFrame(QWidget *parent = nullptr);
    ~SettingsFrame();

    void addGPUInfo(NVidiaSMI *smi);

private:
    Ui::SettingsFrame *ui;
    bool addedGPUInfo;
};

#endif // SETTINGSFRAME_H
