#ifndef QUTIEHELPERS_H
#define QUTIEHELPERS_H

#include <QLayout>
#include <QMessageBox>
#include <QProcess>
#include <QStringList>
#include <QVariant>

class QutieHelpers
{
public:
    QutieHelpers();
    static void clearLayout(QLayout *layout);
    static void msgbox(const QString &title, const QString &msg);
};

#endif // QUTIEHELPERS_H
