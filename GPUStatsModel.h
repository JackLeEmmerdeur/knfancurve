#ifndef GPUSTATSMODEL_H
#define GPUSTATSMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <Qt>
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QMap>
#include <QMapNode>
#include "GPUHelpers.h"
#include "GPU.h"

class GPUStatsModel : public QAbstractTableModel
{
public:

    GPUStatsModel();
    ~GPUStatsModel();

    QMap<int, QStringList> *vals;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QStringList *columns;

    void readAllGPUValues(GPU *gpu);
};

#endif // GPUSTATSMODEL_H
