#ifndef DIA_H
#define DIA_H

#include <QWidget>
#include <QtCharts>
#include <QRunnable>
#include <QSplitter>
#include <QAtomicPointer>
#include <QValueAxis>
#include <QColor>
#include <QAbstractListModel>
#include <QList>
#include <QListView>
#include <QTime>
#include "GPU.h"
#include "GPUHelpers.h"
#include "ChartRepainter.h"
#include "QutieHelpers.h"

namespace Ui {
class ChartWrapper;
}

class ChartDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ChartDataModel(ChartRepainter *repainter);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

public slots:
    void handleGraphTick(double value);

private:
    QList<QList<QVariant> > *graphvalues;
    ChartRepainter *repainter;
};

class ChartWrapper : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWrapper(QWidget *parent = nullptr, GPU *gpu = nullptr, int xAxisTicks = 10,
                          int yAxisTicks = 100, unsigned long refreshMS = 2000,
                          QString caption = nullptr, QString monitorValue = nullptr);
    ~ChartWrapper();

    ChartRepainter *getRepainter();

signals:
    void chartRepainterStopped(ChartRepainter *);

public slots:
    void handleCloseGraphBtn();
    void stoppedChartRepainter(ChartRepainter *repainter);
    void handleGraphTick(double value);

private:
    int xAxisTicks, yAxisTicks;
    Ui::ChartWrapper *ui;

    ChartRepainter *repainter;
    QAtomicPointer<QLineSeries> *series;
    QAtomicPointer<GPU> *nvidiagpu;
    QString caption;
};

#endif // DIA_H
