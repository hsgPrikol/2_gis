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
    std::cout << "process file " <<std::this_thread::get_id() << std::endl;;

    std::thread th([this, filePath](){

        QStringList fileData = m_fileManager->readFile(filePath);

        if (fileData.empty()) {
            return;
        }

        std::unordered_map<QString, std::shared_ptr<WordStats>> map;

        for (const QString& elem : fileData) {

            //            auto elem = elems.toLower();

            std::shared_ptr<WordStats> tmpWs;

            if (map.find(elem) != map.end()) {  //log n
                auto tmp = map[elem];
                tmp->setCount(tmp->count() + 1);
            } else {
                map[elem] = std::make_shared<WordStats>(elem, 1);
            }

            tmpWs = map[elem];

            if (m_viewManager->find(tmpWs)) //log n
            {
                m_viewManager->sort(); //n log n

                if (m_viewManager->size() < 15) {
                    m_viewManager->add(tmpWs);
                } else if (std::prev(m_viewManager->histogramModel()->end())->get()->count() < tmpWs->count()) {
                    m_viewManager->pop_back();
                    m_viewManager->add(tmpWs);
                }
            } else {
                if (m_viewManager->maxRepeatedWord() < tmpWs->count()) {
                    m_viewManager->setMaxRepeatedWord(tmpWs->count());
                }

                m_viewManager->update(m_viewManager->indexOf(tmpWs));
                //                    m_viewManager->histogramModel();
            }


            //            std::cout << tmpWs.get()->word().toStdString() << " " << tmpWs.get()->count() << std::endl;

            std::this_thread::sleep_for(std::chrono::nanoseconds(30));
            //            std::cout << std::endl;
        }

        //        WordCounter wc;

        //        std::map<QString, size_t> wordCount = wc.wordCounter(fileData);

        //        for (const auto& [word, count] : wordCount) {
        //            m_viewManager->add(word, count);
        //        }
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
