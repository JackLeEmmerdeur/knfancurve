#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QLayout>
#include <QDebug>
#include <QFrame>
#include <QList>
#include "categories.h"
#include "diaform.h"
#include "qutiehelpers.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->prevCatIndex = 0;

    ui->setupUi(this);

    QList<QList<QString> > *q = new QList<QList<QString> >();
    q->append(QList<QString>({":/icons/cog", tr("My dude") }));
    q->append(QList<QString>({":/icons/chart_curve", "Charts"}));

    this->cats = new Categories(nullptr, q);

    QFrame *f = ui->categoriesFrame;
    QHBoxLayout *l = new QHBoxLayout();

    f->setLayout(l);
    l->addWidget(this->cats);
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);

    connect(
        this->cats,
        SIGNAL(catIndexChanged(int)),
        this,
        SLOT(handleCatIndexChange(int))
        );
}

void MainWindow::handleCatIndexChange(int index)
{
    if (index == 1 && this->prevCatIndex != 1) {
        QVBoxLayout *contentLayout = static_cast<QVBoxLayout *>(this->ui->contentLayout);
        try {
            if (this->dia == nullptr)
                this->dia = new DiaForm();
            contentLayout->addWidget(dia);
            dia->adjustSize();
        }
        catch (const std::exception &e) {
            qDebug("%s", e.what());
        }
    } else if (index == 0) {
        if (this->prevCatIndex == 1)
            this->dia->setParent(nullptr);
    }
    this->prevCatIndex = index;
}

MainWindow::~MainWindow()
{
    delete this->cats;
    delete ui;
}
