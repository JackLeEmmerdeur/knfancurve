#ifndef GPUHELPERS_H
#define GPUHELPERS_H
#include <QLayout>
#include <QMessageBox>
#include <QProcess>
#include <QStringList>
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QTextCodec>

class GPUHelpers
{
public:
    GPUHelpers();
    static QProcess *createProcess(QStringList args);
    static QProcess *runProcess(const QString &procpath, QStringList args);
    static QVariant *getProcRes(QStringList args, bool getLines);
    static QString readGPUValue(int index, QString gpuvalue);
};

#endif // GPUHELPERS_H
