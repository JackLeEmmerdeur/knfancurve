#include "GPUHelpers.h"

GPUHelpers::GPUHelpers()
{
}

QString GPUHelpers::readGPUValue(int index, QString gpuvalue)
{
    QVariant *v = GPUHelpers::getProcRes({"--query-gpu=" + gpuvalue, "-i", QString::number(index),
                                          "--format=csv,noheader"}, false);

    QString s = v->toString();

    delete v;

    int i = s.indexOf(" ");

    if (i > -1)
        return s.mid(0, i);
}

QVariant *GPUHelpers::getProcRes(QStringList args, bool getLines = false)
{
    QProcess *proc = GPUHelpers::createProcess(args);

    if (proc->waitForStarted() && proc->waitForFinished()) {
        QByteArray procRes = proc->readAllStandardOutput();

        QString procResStr = QTextCodec::codecForMib(106)->toUnicode(procRes);

        if (getLines)
            return new QVariant(procResStr.split(QRegExp("[\r\n]"), QString::SkipEmptyParts));
        else
            return new QVariant(procResStr);
    }

    delete proc;
    return new QVariant("");
}

QProcess *GPUHelpers::createProcess(QStringList args)
{
    QProcess *proc = new QProcess();
    proc->start("nvidia-smi", args);
    return proc;
}
