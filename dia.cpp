#include "dia.h"
#include "ui_dia.h"

DiaRepainter::DiaRepainter(QString monitorValue, QAtomicPointer<NVidiaGPU> *gpu,
                           QAtomicPointer<QChart> *chart, QAtomicPointer<QLineSeries> *series)
{
    this->nvidiagpu = gpu;
    this->monitorValue = monitorValue;
    this->series = series;
    this->chart = chart;
    this->paused = false;
}

DiaRepainter::~DiaRepainter()
{
}

void DiaRepainter::run()
{
    for (int i = 0; i < 10; i++) {
        QString xoxo = GPUHelpers::readGPUValue(this->nvidiagpu->load()->index, this->monitorValue);
        int x = this->series->load()->count();
        qDebug() << xoxo << x;
        this->series->load()->append(x, xoxo.toInt());
        QThread::msleep(1000);
    }
}

void DiaRepainter::resume()
{
    sync.lock();
    this->paused = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void DiaRepainter::pause()
{
    sync.lock();
    this->paused = true;
    sync.unlock();
}

void DiaRepainter::finishTask()
{
}

Dia::Dia(QWidget *parent, NVidiaGPU *gpu, QString caption, QString monitorValue) :
    QChartView(parent),
    ui(new Ui::Dia)
{
    ui->setupUi(this);
    this->nvidiagpu = new QAtomicPointer<NVidiaGPU>(gpu);
    this->caption = caption;
    this->setRenderHint(QPainter::Antialiasing);
    this->init();
    this->repainter = new DiaRepainter(monitorValue, this->nvidiagpu, this->chart, this->series);
}

Dia::~Dia()
{
    qDebug() << "deleting dia";
    delete ui;
    delete this->nvidiagpu;
    delete this->series;
    delete this->chart;
}

DiaRepainter *Dia::getRepainter()
{
    return this->repainter;
}

void Dia::init()
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
    yAxis->setMax(40);

    QAbstractAxis *xAxis = chart->axisX();
    xAxis->setMax(10);

    this->chart = new QAtomicPointer<QChart>();
    this->chart->store(chart);
    this->setChart(chart);
}
