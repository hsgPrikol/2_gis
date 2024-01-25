#ifndef WORDSTATSMODEL_H
#define WORDSTATSMODEL_H

#include <QAbstractListModel>
#include <QDebug>

#include <set>
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

    void addData(const QString& word, size_t count);

    void addData(const std::shared_ptr<WordStats> &ws);

    void removeLastData();

    int maxCount() const;

    void setMaxCount(int newMaxCount);

    void update(int idx);

    size_t size() const;

    QList<std::shared_ptr<WordStats>>::iterator begin() {
        return m_words.begin();
    }

    QList<std::shared_ptr<WordStats>>::iterator end() {
        return m_words.end();
    }

    QList<std::shared_ptr<WordStats>>::const_iterator begin() const {
        return m_words.begin();
    }

    QList<std::shared_ptr<WordStats>>::const_iterator end() const {
        return m_words.end();
    }

    int indexOf(const std::shared_ptr<WordStats>& ws);

private:
    QList<std::shared_ptr<WordStats>> m_words;

//    QList<std::shared_ptr<WordStats>> result;


//    std::set<std::shared_ptr<WordStats>> m_wordsPtr;

    int m_maxCount;

};

#endif // WORDSTATSMODEL_H
