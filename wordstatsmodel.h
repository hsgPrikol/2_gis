#ifndef WORDSTATSMODEL_H
#define WORDSTATSMODEL_H

#include <QAbstractListModel>

#include <memory>

#include "wordstats.h"

class WordStatsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WordStatsModel(QObject *parent = nullptr);

    enum WordStatsRole {
        WORD = Qt::UserRole  + 1,
        COUNT
    };

    Q_ENUM(WordStatsRole)

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QList<std::shared_ptr<WordStats>> m_words;

};

#endif // WORDSTATSMODEL_H
