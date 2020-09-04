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
// for (int i = 0; i < this->ui->gridLayout->count(); ++i) {
// QWidget *w = this->ui->gridLayout->itemAt(i)->widget();
// if (w != nullptr)
// delete w;
// }
    delete this->ui;
}

QVBoxLayout *ChartsWidget::getChartVBoxLayout()
{
    return this->ui->chartVBoxLayout;
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
    ChartWrapper *dia = new ChartWrapper(this, gpu, xAxisTicks, yAxisTicks, refreshMS, caption,
                                         monitorValue);

    splitter->addWidget(dia);

    connect(dia, SIGNAL(chartRepainterStopped(ChartRepainter*)), this,
            SLOT(chartRepainterStopped(ChartRepainter*)));

    splitter->addWidget(dia);

    int vboxlayoutHeight = vboxlayout->geometry().height();

    if (vboxlayoutHeight > 0 && c > 0) {
        int f = vboxlayoutHeight / c;
        qDebug() << f;
        for (int i = 0; i < c; i++)
            vboxlayout->itemAt(i)->geometry().setHeight(f);
    }

    this->graphcount++;
    QThreadPool::globalInstance()->start(dia->getRepainter());
}
