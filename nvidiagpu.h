#ifndef NVIDIAGPU_H
#define NVIDIAGPU_H

#include <QDebug>
#include <QProcess>
#include <QTextCodec>
#include <QString>
#include "qutiehelpers.h"

class NVidiaGPU
{
public:
    QString id;
    QString name;
    int index;

    NVidiaGPU(int index, QString id, QString name);
    void initExtendedInfo();

    friend QDebug operator <<(QDebug, const NVidiaGPU &);
private:
    bool extendedInfoInitialized;
};

#endif // NVIDIAGPU_H
