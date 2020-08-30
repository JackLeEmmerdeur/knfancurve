#include "gpustatsmodel.h"

GPUStatsModel::GPUStatsModel()
{
    this->vals = new QMap<int, QStringList>();
}

GPUStatsModel::~GPUStatsModel()
{
    delete this->columns;

    for (std::pair<int, QStringList> q: this->vals->toStdMap())
        q.second.clear();
    delete this->vals;
}

void GPUStatsModel::readAllGPUValues(NVidiaGPU *gpu)
{
    this->columns = new QStringList({"Name", "Value"});
    this->vals->insert(0,
                       QStringList({"Total Memory",
                                    GPUHelpers::readGPUValue(gpu->index, "memory.total")}));
    this->vals->insert(1,
                       QStringList({"Max. GPU Clock",
                                    GPUHelpers::readGPUValue(gpu->index, "clocks.max.graphics")}));

    this->vals->insert(2,
                       QStringList({"Max. RAM Clock",
                                    GPUHelpers::readGPUValue(gpu->index, "clocks.max.memory")}));
    emit dataChanged(index(0, 0),
                     index(rowCount(), columnCount()));
    emit layoutChanged();
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
            return QString("Name");
        else
            return QString("Wert");
    }
    return QVariant();
}
