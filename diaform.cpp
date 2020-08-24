#include "diaform.h"
#include "ui_diaform.h"

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
