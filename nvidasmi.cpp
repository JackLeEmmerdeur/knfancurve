#include "nvidasmi.h"

NVidiaGPU::NVidiaGPU(QString id, QString name)
{
    this->id = id;
    this->name = name;
}

QDebug operator <<(QDebug stream, const NVidiaGPU &input)
{
    stream << input.name.toStdString().c_str() << "-" << input.id.toStdString().c_str();
    return stream;
}

NVidiaSMI::NVidiaSMI()
{
    this->smipath = MiscHelpers::findBinfile("nvidia-smi");
    this->proc = QutieHelpers::runproc("nvidia-smi", QStringList({"-L"}));

    if (this->proc->waitForStarted()) {
        if (this->proc->waitForFinished()) {
            QByteArray procres = this->proc->readAllStandardOutput();
            QString procresStr = QTextCodec::codecForMib(106)->toUnicode(procres);
            QStringList procResRows = procresStr.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

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
    }

    // this->gpuInfo = new QString(q.data());
    // connect(this->proc, SIGNAL(finished(int)), this, SLOT(finishedReadingGPUInfo(int)));
}

NVidiaSMI::~NVidiaSMI()
{
    if (this->gpus != nullptr)
        delete this->gpus;
    if (this->proc != nullptr)
        delete this->proc;
}

int NVidiaSMI::gpuCount()
{
    if (this->gpus == nullptr) return 0;
    return this->gpus->length();
}

NVidiaGPU *NVidiaSMI::gpu(int index)
{
    if (index > -1 && index < this->gpuCount())
        return this->gpus->at(index);
    return nullptr;
}

// void NVidaSMI::finishedReadingGPUInfo(int processReturnValue)
// {
// if (processReturnValue == 0) {
// QByteArray a = this->proc->readAllStandardOutput();
// QString q = QTextCodec::codecForMib(106)->toUnicode(a);
// this->gpuInfo = new QString(q.data());
// }
// }
