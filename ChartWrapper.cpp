#include "ChartWrapper.h"
#include "ui_dia.h"

ChartRepainter::ChartRepainter(QString monitorValue, QAtomicPointer<GPU> *gpu, int yAxisTicks,
                               int xAxisTicks, unsigned long refreshMS,
                               QAtomicPointer<QChart> *chart, QAtomicPointer<QLineSeries> *series)
{
    this->xAxisTicks = xAxisTicks;
    this->yAxisTicks = yAxisTicks;
    this->refreshMS = refreshMS;
    this->nvidiagpu = gpu;
    this->monitorValue = monitorValue;
    this->series = series;
    this->chart = chart;
    this->canceled = new QAtomicInt(0);
// this->paused = false;
}

ChartRepainter::~ChartRepainter()
{
}

void ChartRepainter::run()
{
    int i = 0;
    while (true) {
        if (this->canceled->load() == 1)
            break;

        QString procRes = GPUHelpers::readGPUValue(
            this->nvidiagpu->load()->index, this->monitorValue);
        double dbl = procRes.toDouble();

        if (i >= this->xAxisTicks+1) {
            QLineSeries *ls = this->series->load();
            QList<QPointF> pl = this->series->load()->points();
            int c = pl.count();
            ls->clear();
            for (int a = 1; a < c; a++)
                ls->append(a-1, pl[a].y());
            ls->append(c-1, dbl);
        } else {
            int x = this->series->load()->count();
            this->series->load()->append(x, dbl);
        }
        QThread::msleep(this->refreshMS);
        i++;
    }
}

void ChartRepainter::cancel()
{
    this->canceled->testAndSetAcquire(0, 1);
}

ChartWrapper::ChartWrapper(QWidget *parent, GPU *gpu, int xAxisTicks, int yAxisTicks,
                           unsigned long refreshMS, QString caption, QString monitorValue) :
    QChartView(parent),
    ui(new Ui::ChartWrapper)
{
    ui->setupUi(this);
    this->xAxisTicks = xAxisTicks;
    this->yAxisTicks = yAxisTicks;
    this->nvidiagpu = new QAtomicPointer<GPU>(gpu);
    this->caption = caption;
    this->setRenderHint(QPainter::Antialiasing);
    this->init();
    this->repainter = new ChartRepainter(monitorValue, this->nvidiagpu, yAxisTicks, xAxisTicks,
                                         refreshMS, this->chart, this->series);
}

ChartWrapper::~ChartWrapper()
{
    delete ui;
    delete this->nvidiagpu;
    delete this->series;
    delete this->chart;
}

ChartRepainter *ChartWrapper::getRepainter()
{
    return this->repainter;
}

void ChartWrapper::init()
{
    this->series = new QAtomicPointer<QLineSeries>();

    QLineSeries *series = new QLineSeries();
    this->series->store(series);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setTitle(this->caption);

    QAbstractAxis *yAxis = chart->axisY();
    yAxis->setMax(this->yAxisTicks);

    QAbstractAxis *xAxis = chart->axisX();
    xAxis->setMax(this->xAxisTicks);

    this->chart = new QAtomicPointer<QChart>();
    this->chart->store(chart);
    this->setChart(chart);
}
