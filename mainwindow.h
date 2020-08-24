#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "categories.h"
#include "diaform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCatIndexChange(int index);

private:
    int prevCatIndex;

    Ui::MainWindow *ui;

    DiaForm *dia = nullptr;

    Categories *cats;
};

#endif // MAINWINDOW_H
