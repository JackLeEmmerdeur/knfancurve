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
#include "SMI.h"

#include "CategoriesWidget.h"
#include "SettingsFrame.h"
#include "ChartsWidget.h"
#include "QutieHelpers.h"

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
    ChartsWidget *dia = nullptr;
    SettingsFrame *settingsFrame = nullptr;
    CategoriesWidget *cats = nullptr;
    SMI *nvidiaSMI = nullptr;

    void createDiaForm();
    void createSettingsFrame();
};

#endif // MAINWINDOW_H
