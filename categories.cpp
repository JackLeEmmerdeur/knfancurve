#include "categories.h"
#include "ui_categories.h"

Categories::Categories(QWidget *parent, QList<QList<QString> > *cats) :
    QWidget(parent),
    ui(new Ui::Categories)
{
    ui->setupUi(this);

    QListView *v = this->ui->categoryList;
    model = new QStandardItemModel(this);

    v->setModel(model);

    int l = cats->length();

    for (int i = 0; i < l; i++) {
        QList<QString> cat = cats->at(i);
        QStandardItem *item = new QStandardItem(QIcon(cat.at(0)), cat.at(1));
        if (i == 0) this->firstCatlistItem = item;
        item->setData(cat.at(2), Qt::UserRole);
        model->appendRow(item);
    }

    connect(
        this->ui->categoryList->selectionModel(),
        SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this,
        SLOT(handleSelectionChanged(QItemSelection,QItemSelection))
        );

    QTimer::singleShot(100, this, SLOT(timeoutDefaultListSelection()));
}

void Categories::timeoutDefaultListSelection()
{
    this->ui->categoryList->selectionModel()->select(
        this->firstCatlistItem->index(), QItemSelectionModel::Select);
}

void Categories::handleSelectionChanged(const QItemSelection &selected,
                                        const QItemSelection &deselected)
{
    if (!selected.indexes().isEmpty()) {
        QModelIndexList l1 = selected.indexes();
        QVariant newCatId = this->ui->categoryList->model()->data(l1.first(), Qt::UserRole);

        QVariant oldCatId;
        QModelIndexList l2 = deselected.indexes();
        if (l2.count() > 0)
            oldCatId = this->ui->categoryList->model()->data(l2.first(), Qt::UserRole);

        emit catIdChanged((oldCatId.isValid() ? oldCatId.toString() : ""), newCatId.toString());
    }
}

Categories::~Categories()
{
    delete ui;
}
