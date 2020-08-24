#include "diaform.h"
#include "ui_diaform.h"
#include <QPainter>
#include <QGridLayout>
#include <QtCharts>
#include <dia.h>

DiaForm::DiaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiaForm)
{
    ui->setupUi(this);
}

DiaForm::~DiaForm()
{
    delete ui;
}

QGridLayout *DiaForm::getGridLayout()
{
    return this->ui->gridLayout;
}

void DiaForm::addGraph()
{
    QGridLayout *grid = this->ui->gridLayout;
    grid->addWidget(new Dia());
}

void DiaForm::on_pushButton_clicked()
{
    this->addGraph();
}
