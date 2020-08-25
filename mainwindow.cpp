#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->prevCatIndex = 0;

    ui->setupUi(this);

    QList<QList<QString> > *q = new QList<QList<QString> >();
    q->append(QList<QString>({":/icons/chart_curve", "Charts", "charts"}));
    q->append(QList<QString>({":/icons/cog", tr("My dude"), "settings"}));

    this->cats = new Categories(nullptr, q);

    QFrame *f = ui->categoriesFrame;
    QHBoxLayout *l = new QHBoxLayout();

    f->setLayout(l);
    l->addWidget(this->cats);
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);

    connect(
        this->cats,
        SIGNAL(catIdChanged(QString,QString)),
        this,
        SLOT(handleCatIndexChange(QString,QString))
        );

    this->proc = new QProcess();
    QStringList procArgs;
    procArgs << "-L";
    this->proc->start("nvidia-smi", procArgs);

    connect(this->proc, SIGNAL(finished(int)),
            this, SLOT(finishedReadingGPUInfo(int)));
}

void MainWindow::finishedReadingGPUInfo(int processReturnValue)
{
    if (processReturnValue == 0) {
        QByteArray a = this->proc->readAllStandardOutput();
        qDebug() << "yo:";
        qDebug() << a.toStdString().c_str();
    }
}

void MainWindow::handleCatIndexChange(const QString &oldCatId, const QString &newCatId)
{
// qDebug("oldCatId=%s / newCatId=%s", oldCatId.toStdString().c_str(),
// newCatId.toStdString().c_str());

    bool newIsCharts = newCatId.compare("charts") == 0;
    bool oldIsCharts = oldCatId.compare("charts") == 0;
    bool newIsSettings = newCatId.compare("settings") == 0;

// qDebug("newIsCharts=%d / oldIsCharts=%d / newIsSettings=%d", newIsCharts, oldIsCharts,
// newIsSettings);

    if (newIsCharts && !oldIsCharts) {
        this->createDiaForm();
    } else if (newIsSettings) {
        if (oldIsCharts && this->dia != nullptr)
            this->dia->setParent(nullptr);
    }
}

MainWindow::~MainWindow()
{
    delete this->cats;
    delete ui;
}

void MainWindow::createDiaForm()
{
    QVBoxLayout *contentLayout = static_cast<QVBoxLayout *>(this->ui->contentLayout);

    if (this->dia == nullptr)
        this->dia = new DiaForm();
    contentLayout->addWidget(dia);
    dia->adjustSize();
}
