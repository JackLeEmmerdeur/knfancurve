#ifndef NVIDASMI_H
#define NVIDASMI_H

#include <QDirIterator>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QDebug>
#include <QProcess>
#include <QTextCodec>
#include <QRegExp>
#include <QMap>
#include <QString>
#include <QStringList>
#include "mischelpers.h"
#include "qutiehelpers.h"

class NVidiaGPU
{
public:
    QString id;
    QString name;

    NVidiaGPU(QString id, QString name);

    friend QDebug operator <<(QDebug, const NVidiaGPU &);
};

class NVidiaSMI
{
public:
    NVidiaSMI();
    ~NVidiaSMI();

    int gpuCount();
    NVidiaGPU *gpu(int index);

private:
    QString smipath;
    QProcess *proc;
    QList<NVidiaGPU *> *gpus = nullptr;

// private slots:
// void finishedReadingGPUInfo(int processReturnValue);
};

#endif // NVIDASMI_H
