#include "nvidiasmi.h"

NVidiaGPU *NVidiaSMI::gpu(int index)
{
    if (index > -1 && index < this->gpuCount())
        return this->gpus->at(index);
    return nullptr;
}

NVidiaSMI::NVidiaSMI()
{
    this->smipath = MiscHelpers::findBinfile("nvidia-smi");
    this->initGPUs();
}

NVidiaSMI::~NVidiaSMI()
{
    if (this->gpus != nullptr)
        delete this->gpus;
}

QProcess *NVidiaSMI::getProcess(QStringList args)
{
    return QutieHelpers::runproc("nvidia-smi", args);
}

void NVidiaSMI::initGPUs()
{
    QProcess *proc = this->getProcess(QStringList({"-L"}));

    if (proc->waitForStarted() && proc->waitForFinished()) {
        QByteArray procRes = proc->readAllStandardOutput();
        QString procResStr = QTextCodec::codecForMib(106)->toUnicode(procRes);
        QStringList procResRows = procResStr.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

        int p, p2;

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
                    this->gpus = new QList<NVidiaGPU *>();
                this->gpus->push_back(new NVidiaGPU(uuid, name));
            }
        }
    }
    delete proc;

    // this->gpuInfo = new QString(q.data());
    // connect(this->proc, SIGNAL(finished(int)), this, SLOT(finishedReadingGPUInfo(int)));
}

int NVidiaSMI::gpuCount()
{
    if (this->gpus == nullptr) return 0;
    return this->gpus->length();
}

int NVidiaSMI::getTemp()
{
    QProcess *proc
        = this->getProcess(QStringList({"--query-gpu=temperature.gpu", "-i", "0",
                                        "--format=csv,noheader"}));
    if (proc->waitForStarted() && proc->waitForFinished()) {
        QByteArray procRes = proc->readAllStandardOutput();
        QString procresStr = QTextCodec::codecForMib(106)->toUnicode(procRes);
        return procresStr.toInt();
    }
    return -1;
}

// void NVidaSMI::finishedReadingGPUInfo(int processReturnValue)
// {
// if (processReturnValue == 0) {
// QByteArray a = this->proc->readAllStandardOutput();
// QString q = QTextCodec::codecForMib(106)->toUnicode(a);
// this->gpuInfo = new QString(q.data());
// }
// }
