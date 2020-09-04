#ifndef DIAFORM_H
#define DIAFORM_H

#include <QWidget>
#include <QGridLayout>
#include <QAction>
#include <QPainter>
#include <QtCharts>
#include <QWidgetAction>
#include <QMenu>
#include <QToolButton>
#include <QSplitter>
#include <QVariant>
#include <QThreadPool>

#include "ChartWrapper.h"
#include "ChartRepainter.h"
#include "GPU.h"

namespace Ui {
class ChartsWidget;
}

class ChartsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartsWidget(QWidget *parent = nullptr);
    ~ChartsWidget();

    QVBoxLayout *getChartVBoxLayout();

    void addGraph(GPU *gpu, int xAxisTicks, int yAxisTicks, unsigned long refreshMS,
                  QString caption, QString monitorValue);

public slots:
    void chartRepainterStopped(ChartRepainter *repainter);

private:
    Ui::ChartsWidget *ui;
    int graphcount = 0;
};

#endif // DIAFORM_H
