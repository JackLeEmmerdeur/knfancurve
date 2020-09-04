#include "QutieHelpers.h"

QutieHelpers::QutieHelpers()
{
}

void QutieHelpers::clearLayout(QLayout *layout)
{
    if (layout) {
        QLayoutItem *item;
        // the key point here is that the layout items are stored inside the layout in a stack
        while ((item = layout->takeAt(0)) != 0) {
            if (item->widget()) {
                layout->removeWidget(item->widget());
                delete item->widget();
            }

            delete item;
        }
    }
}

void QutieHelpers::refreshListView(QAbstractItemModel *m, int startrow, int endrow)
{
    emit m->dataChanged(
        m->index((startrow > -1) ? startrow : 0, 0),
        m->index((endrow > -1 && endrow >= startrow) ? endrow : m->rowCount(), m->columnCount()));
    emit m->layoutChanged();
}

void QutieHelpers::warning(QWidget *parent, QString title, QString msg)
{
    QMessageBox::warning(parent, title, msg, QMessageBox::Ok);
}

void QutieHelpers::msgbox(const QString &title, const QString &msg)
{
    QMessageBox msgbox;
    msgbox.setWindowTitle(title);
    msgbox.setText(msg);
    msgbox.exec();
}
