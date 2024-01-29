#include "wordstatsprocessor.h"

WordStatsProcessor::WordStatsProcessor(QObject *parent)
    : QObject{parent}
//    , m_fileManager(std::make_unique<FileManager>(this))
{

}

WordStatsProcessor::~WordStatsProcessor()
{

}

void WordStatsProcessor::startProcessing()
{
    QFile file(m_filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    size_t fileSize = file.size();
    int bytes = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(" ", Qt::SkipEmptyParts);
        for (QString &word : words) {

            QString normalizedWord;

            for (const QChar &ch : word) {
                if (ch.isLetter()) {
                    normalizedWord.append(ch.toLower());
                }
            }

            if (normalizedWord.isEmpty() || normalizedWord == ""){
                continue;
            }


            bytes += word.size();
            word = word.toLower();

            size_t percentage = static_cast<int>((static_cast<float>(bytes) / fileSize) * 100) * 2;

            emit progressUpdate(percentage);
            emit newWordProcessed(std::move(normalizedWord));
            QThread::usleep(1); // для того, чтобы видеть работу, а то происходит всё молниеносно.
        }
    }

    emit update();
    emit progressUpdate(100);

    file.close();
}

const QString &WordStatsProcessor::filepath() const
{
    return m_filepath;
}

void WordStatsProcessor::setFilepath(const QString &newFilepath)
{
    m_filepath = newFilepath;
}

