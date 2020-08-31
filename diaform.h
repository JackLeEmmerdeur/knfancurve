#ifndef DIAFORM_H
#define DIAFORM_H

#include <QWidget>
#include <QGridLayout>
#include <QAction>
#include <QPainter>
#include <QtCharts>
#include <QWidgetAction>
#include <QMenu>
#include <QToolButton>
#include <QVariant>
#include <QThreadPool>

#include "dia.h"
#include "nvidiagpu.h"

namespace Ui {
class DiaForm;
}

class DiaForm : public QWidget
{
    Q_OBJECT

public:
    explicit DiaForm(QWidget *parent = nullptr);
    ~DiaForm();

    QGridLayout *getGridLayout();

    void addGraph(NVidiaGPU *gpu, QString caption, QString monitorValue);

// private slots:
// void on_pushButton_clicked();

private:
    Ui::DiaForm *ui;
};

#endif // DIAFORM_H
