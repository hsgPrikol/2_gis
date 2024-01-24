#include "qmlviewmanager.h"

QmlViewManager::QmlViewManager(QObject *parent)
    : QObject{parent}
    , m_maxWordCount(0)
    , m_maxRepeatedWord(0)
    , m_processValue(0)
    , m_histogramModel(new WordStatsModel(this))
    , m_proxyModel(new SortFilterModel(this))
{
    init();
}

QmlViewManager::~QmlViewManager()
{
    delete m_histogramModel;
    delete m_proxyModel;
}

int QmlViewManager::maxWordCount() const
{
    return m_maxWordCount;
}

void QmlViewManager::setMaxWordCount(int newMaxWordCount)
{
    if (m_maxWordCount == newMaxWordCount)
        return;
    m_maxWordCount = newMaxWordCount;
    emit maxWordCountChanged();
}

int QmlViewManager::maxRepeatedWord() const
{
    return m_maxRepeatedWord;
}

void QmlViewManager::setMaxRepeatedWord(int newMaxRepeatedWord)
{
    if (m_maxRepeatedWord == newMaxRepeatedWord)
        return;
    m_maxRepeatedWord = newMaxRepeatedWord;
    emit maxRepeatedWordChanged();
}

WordStatsModel *QmlViewManager::histogramModel() const
{
    return m_histogramModel;
}

void QmlViewManager::setHistogramModel(WordStatsModel *newHistogramModel)
{
    if (m_histogramModel == newHistogramModel)
        return;
    m_histogramModel = newHistogramModel;
    emit histogramModelChanged();
}

SortFilterModel *QmlViewManager::proxyModel() const
{
    return m_proxyModel;
}

void QmlViewManager::setProxyModel(SortFilterModel *newProxyModel)
{
    if (m_proxyModel == newProxyModel)
        return;
    m_proxyModel = newProxyModel;
    emit proxyModelChanged();
}

void QmlViewManager::add(const QString& word, int count)
{
    auto max = [this](int count){
        if (count > m_maxRepeatedWord) {
            setMaxRepeatedWord(count);
        }
    };

    max(count);

    ++m_maxWordCount;

    m_histogramModel->addData(word, count);
}

void QmlViewManager::progress(int value)
{
    setProcessValue(value);
}

void QmlViewManager::init()
{
    initProxy();
}

void QmlViewManager::initProxy()
{
    m_proxyModel->setSourceModel(m_histogramModel);
    m_proxyModel->sort(0, Qt::AscendingOrder);
}

int QmlViewManager::processValue() const
{
    return m_processValue;
}

void QmlViewManager::setProcessValue(int newProcessValue)
{
    if (m_processValue == newProcessValue)
        return;
    m_processValue = newProcessValue;
    emit processValueChanged();
}
