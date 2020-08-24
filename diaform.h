#ifndef DIAFORM_H
#define DIAFORM_H

#include <QWidget>

namespace Ui {
class DiaForm;
}

class DiaForm : public QWidget
{
    Q_OBJECT

public:
    explicit DiaForm(QWidget *parent = nullptr);
    ~DiaForm();

private:
    Ui::DiaForm *ui;
};

#endif // DIAFORM_H
