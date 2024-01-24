#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

#include <map>

class WordCounter
{
public:
    WordCounter();

    std::map<QString, size_t> wordCounter(const QStringList &stringList);
};

#endif // WORDCOUNTER_H
