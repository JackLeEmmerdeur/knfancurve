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
#include "GPU.h"
#include "MiscHelpers.h"
#include "QutieHelpers.h"
#include "GPUHelpers.h"

class SMI
{
public:
    SMI();
    ~SMI();

    GPU *gpu(int index);

    QList<GPU *> *gpus = nullptr;

    int getGPUCount();
    int getTemp();
    int getFanSpeed();

private:
    void initGPUs();

    QString smipath;

// private slots:
// void finishedReadingGPUInfo(int processReturnValue);
};

#endif // NVIDASMI_H
