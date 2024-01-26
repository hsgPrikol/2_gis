#ifndef WORDSTATS_H
#define WORDSTATS_H

#include <QString>

class WordStats
{
public:
    WordStats(const QString& word, int count = 1);

    const QString &word() const;
    void setWord(const QString &newWord);

    int count() const;
    void setCount(int newCount);

    bool operator<(const WordStats& other) {
        return m_count < other.m_count;
    }
    bool operator==(const WordStats& other) {
        return m_count == other.m_count;
    }
    bool operator>(const WordStats& other) {
        return m_count > other.m_count;
    }

    WordStats& operator++() {
        ++m_count;
         return *this;
    }

     WordStats operator++(int) {
        WordStats tmp(*this);
        ++m_count;
        return tmp;
    }

private:
    QString m_word;
    int m_count;
};

#endif // WORDSTATS_H
