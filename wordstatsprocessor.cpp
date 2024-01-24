#include "wordstatsprocessor.h"

WordStatsProcessor::WordStatsProcessor(QObject *parent)
    : QObject{parent}
    , m_fileManager(std::make_unique<FileManager>(this))
    , m_viewManager(new QmlViewManager(this))
{
    QObject::connect(&*m_fileManager, &FileManager::progressUpdated, m_viewManager, &QmlViewManager::progress);
}

WordStatsProcessor::~WordStatsProcessor()
{
    delete m_viewManager;
}

void WordStatsProcessor::processFile(const QString& filePath)
{
    std::thread th([this, filePath](){

        QStringList fileData = m_fileManager->readFile(filePath);

        if (fileData.empty()) {
            return;
        }

        WordCounter wc;

        std::map<QString, size_t> wordCount = wc.wordCounter(fileData);

        for (const auto& [word, count] : wordCount) {
            m_viewManager->add(word, count);
        }
    });

    th.detach();
}

void WordStatsProcessor::addObject()
{
    m_viewManager->add("sadasd", 24);
    m_viewManager->setMaxWordCount(m_viewManager->maxWordCount() + 1);
}

QmlViewManager *WordStatsProcessor::viewManager() const
{
    return m_viewManager;
}

void WordStatsProcessor::setViewManager(QmlViewManager *newViewManager)
{
    if (m_viewManager == newViewManager)
        return;
    m_viewManager = newViewManager;
    emit viewManagerChanged();
}
