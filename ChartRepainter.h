#ifndef CHARTREPAINTER_H
#define CHARTREPAINTER_H

#include <QObject>
#include <QRunnable>
#include <QObject>
#include <QLineSeries>
#include <QtCharts>
#include <QAtomicPointer>
#include <QAtomicInt>
#include <Qt>

#include "GPU.h"
#include "GPUHelpers.h"

class ChartRepainter : public QObject, public QRunnable
{
    Q_OBJECT

public:

    ChartRepainter(QObject *parent, QString monitorValue, QAtomicPointer<GPU> *gpu, int yAxisTicks,
                   int xAxisTicks, unsigned long refreshMS, QAtomicPointer<QLineSeries> *series);

    ~ChartRepainter();
    void run();
    void cancel();
    void pauseToggle();

    QObject *getParent();

private slots:
    void handleStoppedFromParent(ChartRepainter *);

signals:
    void graphTicked(double value);
    void stopped(ChartRepainter *);
    void stopRepainter(ChartRepainter *);

private:
    int xAxisTicks, yAxisTicks;
    unsigned long refreshMS;
    QObject *parent;
    QAtomicPointer<GPU> *nvidiagpu;
    QAtomicPointer<QLineSeries> *series = nullptr;
    QAtomicInt *canceled = nullptr;
    QAtomicInt *paused = nullptr;
    QString monitorValue;
};

#endif // CHARTREPAINTER_H
