#include "qutiehelpers.h"

QutieHelpers::QutieHelpers()
{
}

void QutieHelpers::clearLayout(QLayout *layout)
{
    if (layout) {
        QLayoutItem *item;

        // the key point here is that the layout items are stored inside the layout in a stack
        while ((item = layout->takeAt(0)) != 0) {
            qDebug("%s", "rem");
            if (item->widget()) {
                layout->removeWidget(item->widget());
                delete item->widget();
            }

            delete item;
        }
    }
}
