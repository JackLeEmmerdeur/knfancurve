#include "SMI.h"

GPU *SMI::gpu(int index)
{
    if (index > -1 && index < this->getGPUCount())
        return this->gpus->at(index);
    return nullptr;
}

SMI::SMI()
{
    this->smipath = MiscHelpers::findBinfile("nvidia-smi");
    this->initGPUs();
}

SMI::~SMI()
{
    for (auto gpu: *this->gpus)
        delete gpu;
    if (this->gpus != nullptr)
        delete this->gpus;
}

void SMI::initGPUs()
{
    QVariant *procRes = GPUHelpers::getProcRes(QStringList({"-L"}), true);
    QStringList procResRows = procRes->toStringList();
    delete procRes;
    int p, p2, index = 0;

    for (QString procResRow: procResRows) {
        QString uuid("");
        QString name("");
        p = procResRow.indexOf("UUID:");
        if (p > -1) {
            name = procResRow.mid(0, p - 2);
            p2 = procResRow.indexOf(")", p + 6);
            if (p2 > -1)
                uuid = procResRow.mid(p + 6, p2-(p + 6));
        }

        if (uuid.length() > 0) {
            if (this->gpus == nullptr)
                this->gpus = new QList<GPU *>();
            this->gpus->push_back(new GPU(index, uuid, name));
        }
        index++;
    }

    // this->gpuInfo = new QString(q.data());
    // connect(this->proc, SIGNAL(finished(int)), this, SLOT(finishedReadingGPUInfo(int)));
}

int SMI::getGPUCount()
{
    if (this->gpus == nullptr) return 0;
    return this->gpus->length();
}

int SMI::getTemp()
{
    QVariant *procRes
        = GPUHelpers::getProcRes(QStringList({"--query-gpu=temperature.gpu", "-i", "0",
                                              "--format=csv,noheader"}), false);
    return procRes->toInt();
}

int SMI::getFanSpeed()
{
    QVariant *proc = GPUHelpers::getProcRes(QStringList({"--query-gpu=fan.speed", "-i", "0",
                                                         "--format=csv,noheader"}), false);

    QString fsp = proc->toString();
    int i = fsp.indexOf("%");
    fsp = fsp.mid(0, i-1);
    return fsp.toInt();
}
