#include "dia.h"
#include "ui_dia.h"

Dia::Dia(QWidget *parent) :
    QChartView(parent),
    ui(new Ui::Dia)
{
    ui->setupUi(this);
    this->setRenderHint(QPainter::Antialiasing);
    this->init();
}

Dia::~Dia()
{
    delete ui;
}

void Dia::init()
{
    QLineSeries *series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    this->setChart(chart);
}
