#include "dia.h"
#include "ui_dia.h"

Dia::Dia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dia)
{
    ui->setupUi(this);
}

Dia::~Dia()
{
    delete ui;
}
