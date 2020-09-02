#include "MiscHelpers.h"

MiscHelpers::MiscHelpers()
{
}

QString MiscHelpers::findfile(QStringList dirs, QString filename)
{
    QStringList strfilter = QStringList() << filename;
    QString f;

    for (QString bindir: dirs) {
        QDirIterator it(bindir, strfilter, QDir::Files, QDirIterator::NoIteratorFlags);
        if (it.hasNext()) {
            f = it.next();
            break;
        }
    }

    return f;
}

QString MiscHelpers::findBinfile(QString filename)
{
    return MiscHelpers::findfile(MISC_BIN_DIRS, filename);
}
