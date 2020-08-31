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
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QApplication>
#include <QTextCodec>
#include "nvidiasmi.h";

#include "categories.h"
#include "settingsframe.h"
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
    void quit();
    void handleAddSettingsMonitorBtnClicked();

private:

    Ui::MainWindow *ui;
    DiaForm *dia = nullptr;
    SettingsFrame *settingsFrame = nullptr;
    Categories *cats = nullptr;
    NVidiaSMI *nvidiaSMI = nullptr;

    void createDiaForm();
    void createSettingsFrame();
};

#endif // MAINWINDOW_H
