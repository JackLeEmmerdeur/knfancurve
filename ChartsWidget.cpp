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
    delete this->ui;
}

QVBoxLayout *ChartsWidget::getChartVBoxLayout()
{
    return this->ui->chartVBoxLayout;
}

void ChartsWidget::stopAllRepainters(bool quitInProgress)
{
    this->quitInProgress = quitInProgress;
    QVBoxLayout *vboxlayout = this->ui->chartVBoxLayout;
    int c = this->graphcount;
    int cr = static_cast<int>(ceil(c/2));

    for (int i = 0; i < cr; i++) {
        QSplitter *w = static_cast<QSplitter *>(vboxlayout->itemAt(i%2)->widget());
        if (w->count() > 0) {
            ChartWrapper *wr1 = static_cast<ChartWrapper *>(w->widget(0));
            emit stoppedFromParent(wr1->getRepainter());
            if (w->count() > 1) {
                ChartWrapper *wr2 = static_cast<ChartWrapper *>(w->widget(1));
                emit stoppedFromParent(wr2->getRepainter());
            }
        }
    }
}

void ChartsWidget::chartRepainterStopped(ChartRepainter *repainter)
{
    QSplitter *splitter = static_cast<QSplitter *>(repainter->getParent()->parent());
    ChartWrapper *w = static_cast<ChartWrapper *>(repainter->getParent());
    this->ui->chartVBoxLayout->removeWidget(w);
    delete w;
    this->graphcount--;
    if (splitter->count() == 0)
        delete splitter;

    if (this->quitInProgress && this->graphcount == 0)
        emit quitReady();
}

void ChartsWidget::addGraph(GPU *gpu, int xAxisTicks, int yAxisTicks, unsigned long refreshMS,
                            QString caption, QString monitorValue)
{
    QVBoxLayout *vboxlayout = this->ui->chartVBoxLayout;

    int c = this->graphcount;
    int x = c % 2;
    int y = c / 2;

    QSplitter *splitter = nullptr;

    if (x == 0) {
        splitter = new QSplitter(this);
        vboxlayout->addWidget(splitter);
    } else {
        splitter = static_cast<QSplitter *>(vboxlayout->itemAt(y)->widget());
    }

    splitter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    ChartWrapper *dia = new ChartWrapper(this, gpu, xAxisTicks, yAxisTicks, refreshMS, caption,
                                         monitorValue);

    splitter->addWidget(dia);

    connect(dia, SIGNAL(chartRepainterStopped(ChartRepainter*)), this,
            SLOT(chartRepainterStopped(ChartRepainter*)));

    splitter->addWidget(dia);

    this->graphcount++;

    int layoutheight = (static_cast<QWidget *>(this->parent()))->geometry().height();

// splitter->setFixedHeight(layoutheight/graphcount);

    for (int i = 0; i < c; i++) {
        if (i % 2 == 0)
            vboxlayout->itemAt(i%2)->widget()->setFixedHeight(layoutheight/graphcount);
    }

    QThreadPool::globalInstance()->start(dia->getRepainter());
}
