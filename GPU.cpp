#include "GPU.h"

GPU::GPU(int index, QString id, QString name)
{
    this->index = index;
    this->id = id;
    this->name = name;
}

QDebug operator <<(QDebug stream, const GPU &input)
{
    stream << input.name.toStdString().c_str() << "-" << input.id.toStdString().c_str();
    return stream;
}
