#include "ChartWrapper.h"
#include "ui_ChartWrapper.h"

ChartDataModel::ChartDataModel(ChartRepainter *repainter)
{
    this->graphvalues = nullptr;
    this->repainter = repainter;
    connect(this->repainter, SIGNAL(graphTicked(double)), this, SLOT(handleGraphTick(double)));
}

int ChartDataModel::rowCount(const QModelIndex &parent) const
{
    if (this->graphvalues == nullptr)
        return 0;
    return this->graphvalues->count();
}

int ChartDataModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant ChartDataModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if (index.row() >= this->rowCount())
            return QVariant();

        if (role == Qt::DisplayRole) {
            QList<QVariant> q = this->graphvalues->at(index.row());
            if (q.length() > 0)
                return q.at(1);
        }
    }
    return QVariant();
}

QVariant ChartDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0)
            return QString(QObject::tr("Wert"));
    }
    return QVariant();
}

void ChartDataModel::handleGraphTick(double value)
{
    if (graphvalues == nullptr)
        this->graphvalues = new QList<QList<QVariant> >();

    QVariant graphValueTime = QVariant(QTime::currentTime());
    QVariant graphValue = value;
    this->graphvalues->append(QList<QVariant>({graphValueTime, graphValue}));
    int c = this->graphvalues->count();
    QutieHelpers::refreshListView(this);
}

ChartWrapper::ChartWrapper(QWidget *parent, GPU *gpu, int xAxisTicks, int yAxisTicks,
                           unsigned long refreshMS, QString caption, QString monitorValue) :
    QWidget(parent),
    ui(new Ui::ChartWrapper)
{
    ui->setupUi(this);

    this->xAxisTicks = xAxisTicks;
    this->yAxisTicks = yAxisTicks;
    this->nvidiagpu = new QAtomicPointer<GPU>(gpu);
    this->caption = caption;

    connect(this->ui->closeGraphBtn, SIGNAL(clicked()), this, SLOT(handleCloseGraphBtn()));

    QSplitter *splitter = new QSplitter(this);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle(this->caption);
    chart->createDefaultAxes();

    QLineSeries *lineseries = new QLineSeries();
    this->series = new QAtomicPointer<QLineSeries>(lineseries);
    chart->addSeries(lineseries);

    QValueAxis *yAxis = new QValueAxis();
    yAxis->setMax(this->yAxisTicks);
    chart->setAxisY(yAxis, lineseries);

    QValueAxis *xAxis = new QValueAxis();
    xAxis->setMax(this->xAxisTicks);
    chart->setAxisX(xAxis, lineseries);

    QChartView *cv = new QChartView(splitter);
    cv->setRenderHint(QPainter::Antialiasing);
    cv->setChart(chart);
    cv->setParent(this);

    QListView *lv = new QListView(splitter);

    splitter->addWidget(cv);
    splitter->addWidget(lv);
    splitter->setSizes(QList<int>({1, 0}));

    this->ui->graphDataContainer->addWidget(splitter);

    this->repainter = new ChartRepainter(this, monitorValue, this->nvidiagpu, yAxisTicks,
                                         xAxisTicks,
                                         refreshMS, this->series);

    connect(this->repainter, SIGNAL(stopped(ChartRepainter*)), this,
            SLOT(stoppedChartRepainter(ChartRepainter*)));
    connect(this->repainter, SIGNAL(graphTicked(double)), this,
            SLOT(handleGraphTick(double)));
    ChartDataModel *c = new ChartDataModel(this->repainter);
    lv->setModel(c);
}

ChartWrapper::~ChartWrapper()
{
    delete ui;
    delete this->nvidiagpu;
}

void ChartWrapper::stoppedChartRepainter(ChartRepainter *repainter)
{
    emit chartRepainterStopped(repainter);
}

void ChartWrapper::handleCloseGraphBtn()
{
    this->repainter->cancel();
}

void ChartWrapper::handleGraphTick(double value)
{
    QString s = QString::number(value, 'f', 2);

// this->ui->currentGraphValueLCD->setDigitCount(s.length());
    this->ui->currentGraphValueLCD->display(value);
}

ChartRepainter *ChartWrapper::getRepainter()
{
    return this->repainter;
}
