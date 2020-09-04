#include "ChartsWidget.h"
#include "ui_ChartsWidget.h"

ChartsWidget::ChartsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartsWidget)
{
    ui->setupUi(this);
}

ChartsWidget::~ChartsWidget()
{
    for (int i = 0; i < this->ui->gridLayout->count(); ++i) {
        QWidget *w = this->ui->gridLayout->itemAt(i)->widget();
        if (w != nullptr)
            delete w;
    }
    delete this->ui;
}

QGridLayout *ChartsWidget::getGridLayout()
{
    return this->ui->gridLayout;
}

void ChartsWidget::chartRepainterStopped(ChartRepainter *repainter)
{
    ChartWrapper *w = static_cast<ChartWrapper *>(repainter->getParent());
    this->ui->gridLayout->removeWidget(w);
    delete w;
}

void ChartsWidget::addGraph(GPU *gpu, int xAxisTicks, int yAxisTicks, unsigned long refreshMS,
                            QString caption, QString monitorValue)
{
    QGridLayout *grid = this->ui->gridLayout;
    int c = grid->count();
    int x = c % 2;
    int y = c / 2;
    ChartWrapper *dia = new ChartWrapper(this, gpu, xAxisTicks, yAxisTicks, refreshMS, caption,
                                         monitorValue);

    connect(dia, SIGNAL(chartRepainterStopped(ChartRepainter*)), this,
            SLOT(chartRepainterStopped(ChartRepainter*)));

    grid->addWidget(dia, y, x);
    QThreadPool::globalInstance()->start(dia->getRepainter());
}

void ChartsWidget::cancelGraphRepainter(int index)
{
    this->ui->gridLayout->itemAt(index);
}
