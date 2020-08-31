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
    qDebug() << "deleting diaform";
    for (int i = 0; i < this->ui->gridLayout->count(); ++i) {
        QWidget *w = this->ui->gridLayout->itemAt(i)->widget();
        if (w != nullptr)
            delete w;
    }
    delete this->ui;
}

QGridLayout *DiaForm::getGridLayout()
{
    return this->ui->gridLayout;
}

void DiaForm::addGraph(NVidiaGPU *gpu, QString caption, QString monitorValue)
{
    QGridLayout *grid = this->ui->gridLayout;
    int c = grid->count();
    int x = c % 2;
    int y = c / 2;
    Dia *dia = new Dia(nullptr, gpu, caption, monitorValue);
    DiaRepainter *diapainter = dia->getRepainter();
    grid->addWidget(dia, y, x);
    QThreadPool::globalInstance()->start(diapainter);
}

// void DiaForm::on_pushButton_clicked()
// {
// this->addGraph();
// }
