#ifndef MISCHELPERS_H
#define MISCHELPERS_H
#include <QString>
#include <QStringList>
#include <QDirIterator>
#include <QDir>

static QStringList MISC_BIN_DIRS = {
    "/bin",
    "/sbin",
    "/usr/bin",
    "/usr/sbin",
    "/usr/local/bin",
    "/usr/local/sbin"
};

class MiscHelpers
{
public:
    MiscHelpers();
    static QString findfile(QStringList dirs, QString filename);
    static QString findBinfile(QString filename);
};

#endif // MISCHELPERS_H
