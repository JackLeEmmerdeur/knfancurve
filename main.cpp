#include "mainwindow.h"
#include <QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QLocale>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;

    if (translator.load(":/translations/nfancurvytr_de", ":/") == false) {
        QMessageBox msg;
        msg.setText("nono");
        msg.exec();
    }

    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
