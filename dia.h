#ifndef DIA_H
#define DIA_H

#include <QWidget>
#include <QtCharts>
#include <QRunnable>
#include <QAtomicPointer>
#include "nvidiagpu.h"
#include "gpuhelpers.h"

namespace Ui {
class Dia;
}

class DiaRepainter : public QObject, public QRunnable
{
    Q_OBJECT

public:

    DiaRepainter(QString monitorValue, QAtomicPointer<NVidiaGPU> *gpu, int yAxisTicks,
                 int xAxisTicks, unsigned long refreshMS, QAtomicPointer<QChart> *chart,
                 QAtomicPointer<QLineSeries> *series);

    ~DiaRepainter();
    void run();
    void resume();
    void pause();

public slots:
    // you need a signal connected to this slot to exit the loop,
    // otherwise the thread running the loop would remain blocked...
    void finishTask();

private:
    int xAxisTicks, yAxisTicks;
    unsigned long refreshMS;
    QAtomicPointer<NVidiaGPU> *nvidiagpu;
    QAtomicPointer<QChart> *chart;
    QAtomicPointer<QLineSeries> *series;
    QEventLoop _loop;
    QMutex sync;
    QWaitCondition pauseCond;
    QString monitorValue;
    bool paused;
};

class Dia : public QChartView
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = nullptr, NVidiaGPU *gpu = nullptr, int xAxisTicks = 10,
                 int yAxisTicks = 100, unsigned long refreshMS = 2000, QString caption = nullptr,
                 QString monitorValue = nullptr);
    ~Dia();

    void init();

    DiaRepainter *getRepainter();

private:
    int xAxisTicks, yAxisTicks;
    Ui::Dia *ui;
    DiaRepainter *repainter;
    QAtomicPointer<NVidiaGPU> *nvidiagpu;
    QAtomicPointer<QLineSeries> *series;
    QAtomicPointer<QChart> *chart;
    QString caption;
};

#endif // DIA_H
