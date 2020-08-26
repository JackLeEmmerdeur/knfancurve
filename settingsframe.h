#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <QFrame>
#include "nvidasmi.h"

namespace Ui {
class SettingsFrame;
}

class SettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsFrame(QWidget *parent = nullptr);
    ~SettingsFrame();

    void addDebugInfo(NVidiaSMI *smi);

private:
    Ui::SettingsFrame *ui;
};

#endif // SETTINGSFRAME_H
