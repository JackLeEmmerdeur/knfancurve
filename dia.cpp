#include "dia.h"
#include "ui_dia.h"

Dia::Dia(QWidget *parent) :
    QChartView(parent),
    ui(new Ui::Dia)
{
    ui->setupUi(this);
    this->setRenderHint(QPainter::Antialiasing);
    this->init();
    this->repainter = new DiaRepainter(this->chart, this->series);
}

Dia::~Dia()
{
    delete ui;
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
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    this->chart = new QAtomicPointer<QChart>();
    this->chart->store(chart);

    this->setChart(chart);
}
