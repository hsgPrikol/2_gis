#include "wordstatsmodel.h"

WordStatsModel::WordStatsModel(QObject *parent)
    : QAbstractListModel{parent}
    , m_maxCount(0)
{
//    m_words << std::make_shared<WordStats>("aaa", 30);
//    m_words << std::make_shared<WordStats>("zzz", 80);
//    m_words << std::make_shared<WordStats>("abc", 40);
//    m_words << std::make_shared<WordStats>("ccc", 50);
//    m_words << std::make_shared<WordStats>("abq", 60);
//    m_words << std::make_shared<WordStats>("aweb", 10);
//    m_words << std::make_shared<WordStats>("abasd", 31);
//    m_words << std::make_shared<WordStats>("abzxfc", 11);
//    m_words << std::make_shared<WordStats>("axcb", 10);
//    m_words << std::make_shared<WordStats>("abbx", 30);
//    m_words << std::make_shared<WordStats>("abzx", 40);
//    m_words << std::make_shared<WordStats>("abxzc", 50);
//    m_words << std::make_shared<WordStats>("azvb", 10);
//    m_words << std::make_shared<WordStats>("bzx", 110);
//    m_words << std::make_shared<WordStats>("aaaa", 110);
//    m_words << std::make_shared<WordStats>("abzxd", 10);

//    addData("aaa", 30);
//    addData("zzz", 80);
//    addData("abc", 40);
//    addData("ccc", 50);
//    addData("abq", 60);
//    addData("aweb", 10);
//    addData("abasd", 31);
//    addData("abzxfc", 11);
//    addData("axcb", 10);
//    addData("abbx", 30);
//    addData("abzx", 40);
//    addData("abxzc", 50);
//    addData("azvb", 10);
//    addData("bzx", 110);
//    addData("aaaa", 110);
//    addData("abzxd", 10);
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

//    auto word = m_words[index.row()];
    m_words[index.row()];

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

    /*auto word = */m_words[index.row()];

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

void WordStatsModel::addData(const QString& word, size_t count)
{
    const size_t index = m_words.size();
//    beginInsertRows(QModelIndex(), index, index);
    beginResetModel();
    m_words.append(std::make_shared<WordStats>(word, count));
//    endInsertRows();
    endResetModel();

    //    emit dataChanged(index, index, QVector<int>() << WORD);
}

void WordStatsModel::addData(const std::shared_ptr<WordStats>& ws)
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

void WordStatsModel::removeLastData()
{
    m_words.pop_back();
}

int WordStatsModel::maxCount() const
{
    return m_maxCount;
}

void WordStatsModel::setMaxCount(int newMaxCount)
{
    m_maxCount = newMaxCount;
}

void WordStatsModel::update(int idx)
{
    auto modelIndex = index(idx);
    emit dataChanged(modelIndex, modelIndex, QVector<int>() << WordStatsRole::COUNT);
//    beginResetModel();
//    endResetModel();

//    const size_t index = m_words.size();
//    beginInsertRows(QModelIndex(), index, index);
//    endInsertRows();
}

size_t WordStatsModel::size() const
{
    return m_words.size();
}

int WordStatsModel::indexOf(const std::shared_ptr<WordStats>& ws)
{
    return m_words.indexOf(ws);
}
