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

    QGridLayout *getGridLayout();

    void addGraph(GPU *gpu, int xAxisTicks, int yAxisTicks, unsigned long refreshMS,
                  QString caption, QString monitorValue);

    void cancelGraphRepainter(int index);

public slots:
    void chartRepainterStopped(ChartRepainter *repainter);

private:
    Ui::ChartsWidget *ui;
};

#endif // DIAFORM_H
