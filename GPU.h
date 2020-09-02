#ifndef NVIDIAGPU_H
#define NVIDIAGPU_H

#include <QDebug>
#include <QProcess>
#include <QTextCodec>
#include <QString>
#include "QutieHelpers.h"

class GPU
{
public:
    QString id;
    QString name;
    int index;

    GPU(int index, QString id, QString name);

    friend QDebug operator <<(QDebug, const GPU &);
private:
    bool extendedInfoInitialized;
};

#endif // NVIDIAGPU_H
