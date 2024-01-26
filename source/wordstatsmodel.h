#ifndef WORDSTATSMODEL_H
#define WORDSTATSMODEL_H

#include <QAbstractListModel>
#include <QDebug>

#include <memory>
#include <unordered_map>
#include <algorithm>

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

    void append(const QString& word, size_t count);

    void append(const std::shared_ptr<WordStats> &ws);

    void pop_back();

    int maxCount() const;

    void setMaxCount(int newMaxCount);

    void update(int idx);

    void update();

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

    const int SIZE = 15;
};

#endif // WORDSTATSMODEL_H
