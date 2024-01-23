#include "wordstatsmodel.h"

WordStatsModel::WordStatsModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_words << std::make_shared<WordStats>("aaa", 15);
    m_words << std::make_shared<WordStats>("abb", 30);
    m_words << std::make_shared<WordStats>("abc", 20);
    m_words << std::make_shared<WordStats>("abs", 35);
    m_words << std::make_shared<WordStats>("abq", 60);
    m_words << std::make_shared<WordStats>("aweb", 10);
    m_words << std::make_shared<WordStats>("abasd", 31);
    m_words << std::make_shared<WordStats>("abzxfc", 11);
    m_words << std::make_shared<WordStats>("axcb", 10);
    m_words << std::make_shared<WordStats>("abbx", 10);
    m_words << std::make_shared<WordStats>("abzx", 10);
    m_words << std::make_shared<WordStats>("abxzc", 10);
    m_words << std::make_shared<WordStats>("azvb", 10);
    m_words << std::make_shared<WordStats>("bzx", 100);
    m_words << std::make_shared<WordStats>("abzxd", 10);
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

    auto word = m_words[index.row()];

    switch (role) {
    case WordStatsRole::WORD: {
        return word->word();
    }
    case WordStatsRole::COUNT: {
        return QVariant::fromValue(word->count());
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

    auto word = m_words[index.row()];

    switch (role) {
    case WordStatsRole::WORD:{
        word->setWord(value.toString());
        isDo = true;
        break;
    }
    case WordStatsRole::COUNT:{
        word->setCount(value.toUInt());
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
