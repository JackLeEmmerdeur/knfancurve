#ifndef DIA_H
#define DIA_H

#include <QWidget>
#include <QtCharts>
#include <QRunnable>
#include <QAtomicPointer>
#include "GPU.h"
#include "GPUHelpers.h"

namespace Ui {
class ChartWrapper;
}

class ChartRepainter : public QObject, public QRunnable
{
    Q_OBJECT

public:

    ChartRepainter(QString monitorValue, QAtomicPointer<GPU> *gpu, int yAxisTicks, int xAxisTicks,
                   unsigned long refreshMS, QAtomicPointer<QChart> *chart,
                   QAtomicPointer<QLineSeries> *series);

    ~ChartRepainter();
    void run();
    void cancel();
// void resume();
// void pause();

public slots:
    // you need a signal connected to this slot to exit the loop,
    // otherwise the thread running the loop would remain blocked...
// void finishTask();

private:
    int xAxisTicks, yAxisTicks;
    unsigned long refreshMS;
    QAtomicPointer<GPU> *nvidiagpu;
    QAtomicPointer<QChart> *chart;
    QAtomicPointer<QLineSeries> *series;
    QAtomicInt *canceled;
// QEventLoop _loop;
// QMutex sync;
// QWaitCondition pauseCond;
// bool paused;
    QString monitorValue;
};

class ChartWrapper : public QChartView
{
    Q_OBJECT

public:
    explicit ChartWrapper(QWidget *parent = nullptr, GPU *gpu = nullptr, int xAxisTicks = 10,
                          int yAxisTicks = 100, unsigned long refreshMS = 2000,
                          QString caption = nullptr, QString monitorValue = nullptr);
    ~ChartWrapper();

    void init();

    ChartRepainter *getRepainter();

private:
    int xAxisTicks, yAxisTicks;
    Ui::ChartWrapper *ui;
    ChartRepainter *repainter;
    QAtomicPointer<GPU> *nvidiagpu;
    QAtomicPointer<QLineSeries> *series;
    QAtomicPointer<QChart> *chart;
    QString caption;
};

#endif // DIA_H
