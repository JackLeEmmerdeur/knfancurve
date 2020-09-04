#include "ChartRepainter.h"

ChartRepainter::ChartRepainter(QObject *parent, QString monitorValue, QAtomicPointer<GPU> *gpu,
                               int yAxisTicks, int xAxisTicks, unsigned long refreshMS,
                               QAtomicPointer<QLineSeries> *series)
{
    this->parent = parent;
    this->xAxisTicks = xAxisTicks;
    this->yAxisTicks = yAxisTicks;
    this->refreshMS = refreshMS;
    this->nvidiagpu = gpu;
    this->monitorValue = monitorValue;
    this->series = series;
    this->canceled = new QAtomicInt(0);
}

ChartRepainter::~ChartRepainter()
{
}

QObject *ChartRepainter::getParent()
{
    return this->parent;
}

void ChartRepainter::run()
{
    int i = 0;
    while (true) {
        if (this->canceled->load() == 1)
            break;
        QString procRes = GPUHelpers::readGPUValue(
            this->nvidiagpu->load()->index, this->monitorValue);
        if (procRes == "N/A\n")
            break;
        double dbl = procRes.toDouble();

        if (i >= this->xAxisTicks+1) {
            QList<QPointF> pl = this->series->load()->points();
            int c = pl.count();
            this->series->load()->clear();
            for (int a = 1; a < c; a++)
                this->series->load()->append(a-1, pl[a].y());
            this->series->load()->append(c-1, dbl);
        } else {
            this->series->load()->append(this->series->load()->count(), dbl);
        }
        emit graphTicked(dbl);
        QThread::msleep(this->refreshMS);
        i++;
    }
    emit stopped(this);
}

void ChartRepainter::cancel()
{
    this->canceled->testAndSetAcquire(0, 1);
}
