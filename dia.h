#ifndef DIA_H
#define DIA_H

#include <QWidget>
#include <QtCharts>
#include <QRunnable>
#include <QAtomicPointer>

namespace Ui {
class Dia;
}

class DiaRepainter : public QObject, public QRunnable
{
    Q_OBJECT

public:

    DiaRepainter(QAtomicPointer<QChart> *chart, QAtomicPointer<QLineSeries> *series)
    {
        this->series = series;
        this->chart = chart;
        this->paused = false;
    }

    void run()
    {
// _loop.exec();
        // qDebug() << "Hello world from thread" << QThread::currentThread();

        this->series->load()->clear();
        this->series->load()->append(0, 1);
        this->series->load()->append(2, 3);

        QThread::msleep(1000);
        this->series->load()->clear();
        this->series->load()->append(0, 1);
        this->series->load()->append(2, 3);
        this->series->load()->append(4, 6);

        QThread::msleep(1000);
        this->series->load()->clear();
        this->series->load()->append(0, 1);
        this->series->load()->append(2, 3);
        this->series->load()->append(4, 6);
        this->series->load()->append(6, 4);

        QThread::msleep(1000);
        this->series->load()->append(0, 1);
        this->series->load()->append(2, 3);
        this->series->load()->append(4, 6);
        this->series->load()->append(6, 4);
        this->chart->load()->addSeries(this->series->load());

        QThread::msleep(2000);

// this->chart->load()->removeSeries(this->series->load());
        this->series->load()->clear();
        this->series->load()->append(0, 3);
        this->series->load()->append(2, 6);
        this->series->load()->append(4, 4);
        this->series->load()->append(6, 2);

        QThread::msleep(2000);
        this->series->load()->clear();
        this->series->load()->append(0, 6);
        this->series->load()->append(2, 4);
        this->series->load()->append(4, 2);
        this->series->load()->append(6, 3);
// this->chart->load()->addSeries(this->series->load());
// this->chart->load()->addSeries(this->series->load());

// QThread::sleep(2000);

// QThread::sleep(2000);

        // this->series->append(2, 4);
        // this->series->append(3, 8);
        // this->series->append(7, 4);
        // this->series->append(10, 5);
    }

    void resume()
    {
        sync.lock();
        this->paused = false;
        sync.unlock();
        pauseCond.wakeAll();
    }

    void pause()
    {
        sync.lock();
        this->paused = true;
        sync.unlock();
    }

public slots:
    // you need a signal connected to this slot to exit the loop,
    // otherwise the thread running the loop would remain blocked...
    void finishTask()
    {
// _loop.exit();
        // _loop
    }

private:
    QEventLoop _loop;
    QAtomicPointer<QChart> *chart;
    QAtomicPointer<QLineSeries> *series;
    QMutex sync;
    QWaitCondition pauseCond;
    bool paused;
};

class Dia : public QChartView
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = nullptr);
    ~Dia();

    void init();

    DiaRepainter *getRepainter();

private:
    Ui::Dia *ui;
    DiaRepainter *repainter;
    QAtomicPointer<QLineSeries> *series;
    QAtomicPointer<QChart> *chart;
};

#endif // DIA_H
