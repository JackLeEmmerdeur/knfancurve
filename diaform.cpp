#include "diaform.h"
#include "ui_diaform.h"

DiaForm::DiaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiaForm)
{
    ui->setupUi(this);
    QMenu *menu = new QMenu("Menu");
    QAction *a1 = menu->addAction(tr("GPU Fanspeed"));
    QAction *a2 = menu->addAction(tr("GPU Temperature"));

    a1->setData(0);
    a2->setData(1);

    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(handleAddGraphMenuChanged(QAction*)));

    QToolButton *b = ui->addGraphButton;
    b->setPopupMode(QToolButton::ToolButtonPopupMode::MenuButtonPopup);
    b->setMenu(menu);
}

DiaForm::~DiaForm()
{
    delete ui;
}

void DiaForm::handleAddGraphMenuChanged(QAction *action)
{
    QVariant v = action->data();
    int index = v.toInt();

    if (index == 0)
        this->addGraph();
    else if (index == 1)
        this->addGraph();
}

QGridLayout *DiaForm::getGridLayout()
{
    return this->ui->gridLayout;
}

void DiaForm::addGraph()
{
    QGridLayout *grid = this->ui->gridLayout;
    int c = grid->count();
    int x = c % 2;
    qDebug("%d,%d", c, x);

    grid->addWidget(new Dia());
}

// void DiaForm::on_pushButton_clicked()
// {
// this->addGraph();
// }
