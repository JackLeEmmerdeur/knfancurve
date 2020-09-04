#ifndef CHARTREPAINTER_H
#define CHARTREPAINTER_H

#include <QObject>
#include <QRunnable>
#include <QObject>
#include <QLineSeries>
#include <QtCharts>
#include <QAtomicPointer>
#include <QAtomicInt>

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

    QObject *getParent();

signals:
    void graphTicked(double value);
    void stopped(ChartRepainter *);

private:
    int xAxisTicks, yAxisTicks;
    unsigned long refreshMS;
    QObject *parent;
    QAtomicPointer<GPU> *nvidiagpu;
    QAtomicPointer<QLineSeries> *series = nullptr;
    QAtomicInt *canceled;
    QString monitorValue;
};

#endif // CHARTREPAINTER_H
