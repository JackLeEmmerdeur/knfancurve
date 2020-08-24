#ifndef DIA_H
#define DIA_H

#include <QWidget>

namespace Ui {
class Dia;
}

class Dia : public QWidget
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = nullptr);
    ~Dia();

private:
    Ui::Dia *ui;
};

#endif // DIA_H
