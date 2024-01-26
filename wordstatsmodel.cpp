#include "wordstatsmodel.h"

WordStatsModel::WordStatsModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int WordStatsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_words.size();
}

QVariant WordStatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case WordStatsRole::WORD: {
        return m_words[index.row()]->word();
    }
    case WordStatsRole::COUNT: {
        return QVariant::fromValue(m_words[index.row()]->count());
    }
    default:
        break;
    }

    return QVariant();
}

bool WordStatsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    bool isDo = false;

    switch (role) {
    case WordStatsRole::WORD:{
        m_words[index.row()]->setWord(value.toString());
        isDo = true;
        break;
    }
    case WordStatsRole::COUNT:{
        m_words[index.row()]->setCount(value.toUInt());
        isDo = true;
        break;
    }
    default:
        break;
    }

    if (isDo) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

QHash<int, QByteArray> WordStatsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[WordStatsRole::WORD] = "word";
    roles[WordStatsRole::COUNT] = "count";

    return roles;
}

void WordStatsModel::append(const QString& word, size_t count)
{
    const size_t index = m_words.size();
    //    beginInsertRows(QModelIndex(), index, index);
    beginResetModel();
    m_words.append(std::make_shared<WordStats>(word, count));
    //    endInsertRows();
    endResetModel();

    //    emit dataChanged(index, index, QVector<int>() << WORD);
}

void WordStatsModel::append(const std::shared_ptr<WordStats>& ws)
{
    const size_t idx = m_words.size() - 1;
    //    auto modelIndex = index(idx);
    beginResetModel();
    //    beginInsertRows(QModelIndex(), idx, idx);
    m_words.append(ws);
    //    endInsertRows();
    //    emit dataChanged(modelIndex, modelIndex, QVector<int>() << WordStatsRole::COUNT);
    endResetModel();
}

void WordStatsModel::pop_back()
{
    m_words.pop_back();
}

void WordStatsModel::update(int idx)
{
    auto modelIndex = index(idx);
    emit dataChanged(modelIndex, modelIndex, QVector<int>() << WordStatsRole::COUNT);
}

void WordStatsModel::update()
{
    beginResetModel();
    endResetModel();
}

size_t WordStatsModel::size() const
{
    return m_words.size();
}

int WordStatsModel::indexOf(const std::shared_ptr<WordStats>& ws)
{
    return m_words.indexOf(ws);
}
