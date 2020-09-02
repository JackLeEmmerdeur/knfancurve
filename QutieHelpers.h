#ifndef QUTIEHELPERS_H
#define QUTIEHELPERS_H

#include <QLayout>
#include <QMessageBox>
#include <QProcess>
#include <QStringList>
#include <QAbstractItemModel>
#include <QVariant>

class QutieHelpers
{
public:
    QutieHelpers();
    static void clearLayout(QLayout *layout);
    static void msgbox(const QString &title, const QString &msg);
    static void refreshListView(QAbstractItemModel *m);
    static void warning(QWidget *parent, QString title, QString msg);
};

#endif // QUTIEHELPERS_H
