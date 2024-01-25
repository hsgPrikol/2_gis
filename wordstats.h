#ifndef WORDSTATS_H
#define WORDSTATS_H

#include <QString>

class WordStats
{
public:
    WordStats(const QString& word, size_t count = 1);

    const QString &word() const;
    void setWord(const QString &newWord);

    size_t count() const;
    void setCount(size_t newCount);

    bool operator<(const WordStats& other) {
        return m_count < other.m_count;
    }
//    bool operator==(const WordStats& other) {
//        return m_count == other.m_count;
//    }
//    bool operator>(const WordStats& other) {
//        return m_count > other.m_count;
//    }

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
    size_t m_count;
};

#endif // WORDSTATS_H
