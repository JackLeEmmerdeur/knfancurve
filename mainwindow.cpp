#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
// const QString DRIVER("QSQLITE");

// if (!QSqlDatabase::isDriverAvailable(DRIVER)) {
// QutieHelpers::msgbox(tr("Error"), tr("SQLiteDriver missing"));
// QTimer::singleShot(1000, this, SLOT(quit()));
// } else {
    ui->setupUi(this);

    this->nvidiaSMI = new NVidiaSMI();

    qDebug() << this->nvidiaSMI->getTemp();
    qDebug() << this->nvidiaSMI->getFanSpeed();

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

// connect(
// this->
// )
// }
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::handleCatIndexChange(const QString &oldCatId, const QString &newCatId)
{
    bool newIsCharts = newCatId.compare("charts") == 0;
    bool oldIsCharts = oldCatId.compare("charts") == 0;
    bool oldIsSettings = oldCatId.compare("settings") == 0;
    bool newIsSettings = newCatId.compare("settings") == 0;

    if (newIsCharts && !oldIsCharts) {
        this->createDiaForm();
        if (oldIsSettings && this->settingsFrame != nullptr)
            this->settingsFrame->setParent(nullptr);
    } else if (newIsSettings) {
        if (this->dia != nullptr)
            this->dia->setParent(nullptr);
        this->createSettingsFrame();
    }
}

MainWindow::~MainWindow()
{
    if (this->nvidiaSMI != nullptr)
        delete this->nvidiaSMI;
    if (this->cats != nullptr)
        delete this->cats;
    if (this->ui != nullptr)
        delete ui;
}

void MainWindow::createSettingsFrame()
{
    QVBoxLayout *contentLayout = static_cast<QVBoxLayout *>(this->ui->contentLayout);
    if (this->settingsFrame == nullptr)
        this->settingsFrame = new SettingsFrame();
    contentLayout->addWidget(this->settingsFrame);
    this->settingsFrame->adjustSize();
    this->settingsFrame->readAllGPUInfo(this->nvidiaSMI);
    this->settingsFrame->selectGPU(0);
}

void MainWindow::createDiaForm()
{
    QVBoxLayout *contentLayout = static_cast<QVBoxLayout *>(this->ui->contentLayout);

    if (this->dia == nullptr)
        this->dia = new DiaForm();
    contentLayout->addWidget(this->dia);
    this->dia->adjustSize();
}
