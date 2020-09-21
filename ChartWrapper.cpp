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

QList<QList<QVariant> > *ChartDataModel::getGraphValues()
{
    return this->graphvalues;
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

    connect(this->ui->closeGraphBtn, SIGNAL(clicked()), this, SLOT(handleClickedCloseGraphBtn()));
    connect(this->ui->showGraphDataBtn, SIGNAL(clicked()), this,
            SLOT(handleClickedGraphDataButton()));
    connect(this->ui->exportDataToolBtn, SIGNAL(clicked()), this,
            SLOT(handleClickedExportDataToolBtn()));

    this->splitter = new QSplitter(this);
    this->splitter->setMinimumHeight(100);

    QChart *chart = new QChart();
    chart->setMinimumHeight(100);
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

    QChartView *cv = new QChartView(this->splitter);
    cv->setRenderHint(QPainter::Antialiasing);
    cv->setChart(chart);
    cv->setParent(this);
    cv->setMinimumSize(QSize(100, 100));

    this->graphDataListView = new QListView(this->splitter);
    this->splitter->addWidget(cv);
    this->splitter->addWidget(this->graphDataListView);
    this->splitter->setSizes(QList<int>({1, 0}));

    this->ui->graphDataContainer->addWidget(this->splitter);
    this->repainter = new ChartRepainter(this, monitorValue, this->nvidiagpu, yAxisTicks,
                                         xAxisTicks,
                                         refreshMS, this->series);
    this->repainter->setProperty("name", monitorValue);

    connect(this->repainter, SIGNAL(stopped(ChartRepainter*)), this,
            SLOT(handleStoppedChartRepainter(ChartRepainter*)));

    connect(this->repainter, SIGNAL(graphTicked(double)), this,
            SLOT(handleGraphTick(double)));

    connect(parent, SIGNAL(stoppedFromParent(ChartRepainter*)), this,
            SLOT(handleStoppedFromParent(ChartRepainter*)));

    this->graphDataListView->setModel(new ChartDataModel(this->repainter));
}

ChartWrapper::~ChartWrapper()
{
    delete ui;
    delete this->nvidiagpu;
}

void ChartWrapper::handleStoppedChartRepainter(ChartRepainter *repainter)
{
    emit chartRepainterStopped(repainter);
}

void ChartWrapper::handleStoppedFromParent(ChartRepainter *repainter)
{
    emit stoppedFromParent(repainter);
}

void ChartWrapper::handleClickedCloseGraphBtn()
{
    this->repainter->cancel();
}

void ChartWrapper::handleClickedExportDataToolBtn()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Graph-Data"), "",
                                                    tr("Comma Separated (*.csv)"));

    ChartDataModel *m = static_cast<ChartDataModel *>(this->graphDataListView->model());

    QFile out(fileName);

    if (!out.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QutieHelpers::warning(this, tr("Error"), tr("Could not create File"));
        return;
    }

    QTextStream s(&out);

    this->getRepainter()->pauseToggle();
    QList<QList<QVariant> > *gd = m->getGraphValues();
    QListIterator<QList<QVariant> > it(*gd);
    while (it.hasNext()) {
        QList<QVariant> v = it.next();
        s << v.at(0).toString() << "," << v.at(1).toString() << "\n";
    }
    out.close();
    this->getRepainter()->pauseToggle();
}

void ChartWrapper::handleClickedGraphDataButton()
{
    if (this->graphDataShown)
        this->splitter->setSizes({1, 0});
    else
        this->splitter->setSizes({2, 1});
    this->graphDataShown = !this->graphDataShown;
}

void ChartWrapper::handleGraphTick(double value)
{
    this->ui->currentGraphValueLCD->display(QString::number(value, 'f', 2));
}

ChartRepainter *ChartWrapper::getRepainter()
{
    return this->repainter;
}
