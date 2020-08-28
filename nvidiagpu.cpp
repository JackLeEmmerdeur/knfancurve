#include "nvidiagpu.h"

NVidiaGPU::NVidiaGPU(QString id, QString name)
{
    this->id = id;
    this->name = name;
}

void NVidiaGPU::initExtendedInfo()
{
// QProcess *proc = QutieHelpers::runproc("nvidia-smi", "xoxo");
// QByteArray procres = proc->readAllStandardOutput();
// QString procresStr = QTextCodec::codecForMib(106)->toUnicode(procres);
// QStringList procResRows = procresStr.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

// delete proc;
// this->extendedInfoInitialized = true;
}

QDebug operator <<(QDebug stream, const NVidiaGPU &input)
{
    stream << input.name.toStdString().c_str() << "-" << input.id.toStdString().c_str();
    return stream;
}
