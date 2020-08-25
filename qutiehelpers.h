#ifndef QUTIEHELPERS_H
#define QUTIEHELPERS_H

#include <QLayout>
#include <QMessageBox>
#include <QProcess>
#include <QStringList>

class QutieHelpers
{
public:
    QutieHelpers();
    static void clearLayout(QLayout *layout);
    static void msgbox(const QString &title, const QString &msg);
    static QProcess *runproc(const QString &procpath, QStringList args);
};

#endif // QUTIEHELPERS_H
