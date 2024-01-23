#ifndef WORDSTATS_H
#define WORDSTATS_H

#include <QString>

class WordStats
{
public:
    WordStats(const QString& word, size_t count);

    const QString &word() const;
    void setWord(const QString &newWord);

    size_t count() const;
    void setCount(size_t newCount);

private:
    QString m_word;
    size_t m_count;
};

#endif // WORDSTATS_H
