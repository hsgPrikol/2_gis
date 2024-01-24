#include "wordcounter.h"

WordCounter::WordCounter()
{

}

std::map<QString, size_t> WordCounter::wordCounter(const QStringList& stringList)
{
    std::map<QString, size_t> wordCount;

    auto test = [](const QString& input) {
        QString result = input;
        result.remove(QRegExp("[^a-zA-Z ]"));
        result = result.simplified();
        return result;
    };

    for (const QString& line : stringList) {

        QString clean = test(line);
        QStringList words = line.split(" ");

        qDebug() << words;

        for (const QString& word : words) {
            QString lowerCaseWord = word.toLower();

            if (wordCount.find(lowerCaseWord) != wordCount.end()) {
                wordCount[lowerCaseWord]++;
            } else {
                wordCount[lowerCaseWord] = 1;
            }
        }
    }

    return wordCount;
}
