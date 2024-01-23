#include "wordstats.h"

WordStats::WordStats(const QString& word, size_t count)
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

size_t WordStats::count() const
{
    return m_count;
}

void WordStats::setCount(size_t newCount)
{
    m_count = newCount;
}
