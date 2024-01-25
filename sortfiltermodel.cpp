#include "sortfiltermodel.h"

SortFilterModel::SortFilterModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}


bool SortFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftWord = sourceModel()->data(left, Qt::UserRole + 1);
    QVariant rightWord = sourceModel()->data(right, Qt::UserRole + 1);

    QVariant leftCount = sourceModel()->data(left, Qt::UserRole + 2);
    QVariant rightCount = sourceModel()->data(right, Qt::UserRole + 2);

//    if (leftCount.toInt() != rightCount.toInt()) {
//        return leftCount.toInt() > rightCount.toInt();
//    }

    return leftWord.toString() < rightWord.toString();
}
