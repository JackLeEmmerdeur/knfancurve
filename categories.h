#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelection>


namespace Ui {
class Categories;
}

class Categories : public QWidget
{
    Q_OBJECT

public:
    explicit Categories(QWidget *parent = nullptr,  QList<QList<QString>> *cats = nullptr);
    ~Categories();

private:
    Ui::Categories *ui;
    QStandardItemModel *model;

signals:
    void catIndexChanged(int index);

private slots:
    void handleSelectionChanged(const QItemSelection& selection);
};

#endif // CATEGORIES_H
