#include "wordstats.h"

WordStats::WordStats(const QString& word, int count)
    : m_word(word)
    , m_count(count)
{

}

const QString &WordStats::word() const
{
    return m_word;
}

void WordStats::setWord(const QString &newWord)
{
    m_word = newWord;
}

int WordStats::count() const
{
    return m_count;
}

void WordStats::setCount(int newCount)
{
    m_count = newCount;
}
