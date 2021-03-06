#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelection>
#include <QList>
#include <QDebug>
#include <QListView>
#include <QIcon>
#include <QModelIndexList>
#include <QMap>
#include <QVariant>
#include <Qt>
#include <QTimer>

namespace Ui {
class CategoriesWidget;
}

class CategoriesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriesWidget(QWidget *parent = nullptr, QList<QList<QString> > *cats = nullptr);
    ~CategoriesWidget();

    void selectCategory(QString catId);

private:
    Ui::CategoriesWidget *ui;
    QStandardItemModel *model;
    QStandardItem *firstCatlistItem;

signals:
    void catIdChanged(const QString &oldCatId, const QString &newCatId);

private slots:
    void handleSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void timeoutDefaultListSelection();
};

#endif // CATEGORIES_H
