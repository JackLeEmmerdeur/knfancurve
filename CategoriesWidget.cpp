#include "CategoriesWidget.h"
#include "ui_CategoriesWidget.h"

CategoriesWidget::CategoriesWidget(QWidget *parent, QList<QList<QString> > *cats) :
    QWidget(parent),
    ui(new Ui::CategoriesWidget)
{
    ui->setupUi(this);

    QListView *v = this->ui->categoryList;
    model = new QStandardItemModel(v);

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

void CategoriesWidget::timeoutDefaultListSelection()
{
    this->ui->categoryList->selectionModel()->select(
        this->firstCatlistItem->index(), QItemSelectionModel::Select);
}

void CategoriesWidget::handleSelectionChanged(const QItemSelection &selected,
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

CategoriesWidget::~CategoriesWidget()
{
    delete ui;
}

void CategoriesWidget::selectCategory(QString catId)
{
    QModelIndex found;
    QStandardItemModel *m = static_cast<QStandardItemModel *>(this->ui->categoryList->model());
    for (int i = 0; i < m->rowCount(); i++) {
        QModelIndex index = m->index(i, 0);
        QVariant v = index.data(Qt::UserRole);
        QString s = v.toString();
        if (s.compare(catId, Qt::CaseSensitivity::CaseInsensitive) == 0) {
            found = index;
            break;
        }
    }
    if (found.isValid())
        this->ui->categoryList->setCurrentIndex(found);
}
