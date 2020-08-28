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
#include <QList>
#include <iterator>
#include "nvidiagpu.h"
#include "mischelpers.h"
#include "qutiehelpers.h"

class NVidiaSMI
{
public:
    NVidiaSMI();
    ~NVidiaSMI();

    NVidiaGPU *gpu(int index);

    QList<NVidiaGPU *> *gpus = nullptr;

    int gpuCount();

    int getTemp();

private:
    void initGPUs();

    QProcess *getProcess(QStringList args);

    QString smipath;

// private slots:
// void finishedReadingGPUInfo(int processReturnValue);
};

#endif // NVIDASMI_H
