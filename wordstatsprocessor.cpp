#include "wordstatsprocessor.h"

WordStatsProcessor::WordStatsProcessor(QObject *parent)
    : QObject{parent}
    , m_fileManager(std::make_unique<FileManager>(this))
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
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(" ", Qt::SkipEmptyParts);
        for (const QString &word : words) {
            emit newWordProcessed(word);
            QThread::usleep(1); // для того, чтобы видеть работу, а то происходит всё молниеносно.
        }
    }

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

