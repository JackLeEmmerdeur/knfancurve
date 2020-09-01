#include "gpustatsmodel.h"

GPUStatsModel::GPUStatsModel()
{
    this->vals = new QMap<int, QStringList>();
    this->columns = new QStringList({QObject::tr("Name"), tr("Value")});
}

GPUStatsModel::~GPUStatsModel()
{
    delete this->columns;

    QMapIterator<int, QStringList> i(*this->vals);
    while (i.hasNext()) {
        i.next();
        i.value().empty();
    }

    delete this->vals;
}

int GPUStatsModel::rowCount(const QModelIndex &parent) const
{
    return this->vals->count();
}

int GPUStatsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant GPUStatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= this->rowCount())
        return QVariant();

    if (role == Qt::DisplayRole) {
        QStringList q = this->vals->value(index.row());
        if (q.length() > 0)
            return q.at(index.column());
    }

    return QVariant();
}

QVariant GPUStatsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0)
            return QString(QObject::tr("Name"));
        else
            return QString(QObject::tr("Value"));
    }
    return QVariant();
}
