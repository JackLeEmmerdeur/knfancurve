#include "categories.h"
#include "ui_categories.h"
#include <QList>
#include <QDebug>
#include <QListView>
#include <QStandardItem>
#include <QIcon>

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
        // qDebug("%s/%s", cat.at(0).toStdString().c_str(), cat.at(1).toStdString().c_str());
        model->appendRow(new QStandardItem(QIcon(cat.at(0)), cat.at(1)));
    }

    connect(
        this->ui->categoryList->selectionModel(),
        SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this,
        SLOT(handleSelectionChanged(QItemSelection))
        );
}

void Categories::handleSelectionChanged(const QItemSelection &selection)
{
    if (selection.indexes().isEmpty()) {
        // clearMainView();
    } else {
        emit catIndexChanged(selection.indexes()[0].row());
    }
}

Categories::~Categories()
{
    delete ui;
}
