#ifndef SORTFILTERMODEL_H
#define SORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class SortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SortFilterModel(QObject *parent = nullptr);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // SORTFILTERMODEL_H
