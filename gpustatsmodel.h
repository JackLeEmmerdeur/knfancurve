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
#include "gpuhelpers.h"
#include "nvidiagpu.h"

class GPUStatsModel : public QAbstractTableModel
{
public:
    GPUStatsModel();
    ~GPUStatsModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void readAllGPUValues(NVidiaGPU *gpu);

private:
    QMap<int, QStringList> *vals;
    QStringList *columns;
};

#endif // GPUSTATSMODEL_H
