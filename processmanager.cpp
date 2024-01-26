#include "processmanager.h"

ProcessManager::ProcessManager(QObject *parent)
    : QObject{parent}
    , m_processThread(new QThread(this))
    , m_process(new WordStatsProcessor)
    , m_viewManager(new QmlViewManager(this))
{
    init();
}

ProcessManager::~ProcessManager()
{
//    m_processThread->quit();
//    m_processThread->wait();
}

QmlViewManager *ProcessManager::viewManager() const
{
    return m_viewManager;
}

void ProcessManager::setViewManager(QmlViewManager *newViewManager)
{
    if (m_viewManager == newViewManager)
        return;
    m_viewManager = newViewManager;
    emit viewManagerChanged();
}

void ProcessManager::startProcessing(const QString &filepath)
{
    m_process->setFilepath(filepath);
    QMetaObject::invokeMethod(m_process, "startProcessing", Qt::QueuedConnection);
    m_processThread->start(QThread::LowestPriority);
}

void ProcessManager::wordAdded(const QString &word)
{
//    m_viewManager->histogramModel()->addData(word, 1);
    m_viewManager->addOrUpdate(word);
}

void ProcessManager::init()
{
    initProcessThread();
}

void ProcessManager::initProcessThread()
{
    m_process->moveToThread(m_processThread);

    connect(m_process, &WordStatsProcessor::newWordProcessed, this, &ProcessManager::wordAdded);
    connect(m_processThread, &QThread::started, m_process, &WordStatsProcessor::startProcessing);
    connect(m_processThread, &QThread::finished, m_process, &WordStatsProcessor::deleteLater);
}
