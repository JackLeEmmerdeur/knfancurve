#ifndef DIAFORM_H
#define DIAFORM_H

#include <QWidget>
#include <QGridLayout>

namespace Ui {
class DiaForm;
}

class DiaForm : public QWidget
{
    Q_OBJECT

public:
    explicit DiaForm(QWidget *parent = nullptr);
    ~DiaForm();

    QGridLayout *getGridLayout();

    void addGraph();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DiaForm *ui;
};

#endif // DIAFORM_H
