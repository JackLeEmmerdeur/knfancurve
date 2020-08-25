#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QLayout>
#include <QDebug>
#include <QFrame>
#include <QList>
#include <QProcess>
#include <QByteArray>
#include <QStringList>
#include "categories.h"
#include "diaform.h"
#include "qutiehelpers.h"

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
    void handleCatIndexChange(const QString &oldCatId, const QString &newCatId);
    void finishedReadingGPUInfo(int processReturnValue);

private:
    int prevCatIndex;

    Ui::MainWindow *ui;

    DiaForm *dia = nullptr;

    Categories *cats;

    QProcess *proc;

    void createDiaForm();
};

#endif // MAINWINDOW_H
