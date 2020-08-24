#ifndef DIA_H
#define DIA_H

#include <QWidget>
#include <QtCharts>

namespace Ui {
class Dia;
}

class Dia : public QChartView
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = nullptr);
    ~Dia();

    void init();

private:
    Ui::Dia *ui;
};

#endif // DIA_H
