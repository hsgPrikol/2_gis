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

    setMaxWordCount(++m_maxWordCount);

    m_histogramModel->append(word, count);
}

void QmlViewManager::add(const std::shared_ptr<WordStats>& ws)
{
    auto max = [this](int count){
        if (count > m_maxRepeatedWord) {
            setMaxRepeatedWord(count);
        }
    };

    max(ws->count());

    setMaxWordCount(++m_maxWordCount);

    m_histogramModel->append(ws);

}

void QmlViewManager::addOrUpdate(const QString &word)
{
    std::shared_ptr<WordStats> tmpWs;

    if (m_unData.find(word) != m_unData.end()) {
        auto tmp = m_unData[word];
        tmp->setCount(tmp->count() + 1);
    } else {
        m_unData[word] = std::make_shared<WordStats>(word);
    }

    tmpWs = m_unData[word];

    if (find(tmpWs)) {

        sort();

        if (m_histogramModel->size() < 15) {
            m_histogramModel->append(tmpWs);
        } else if (std::prev(m_histogramModel->end())->get()->count() < tmpWs->count()) {
            m_histogramModel->pop_back();
            m_histogramModel->append(tmpWs);
        }
    } else {
        if (m_maxRepeatedWord < tmpWs->count()) {
            setMaxRepeatedWord(tmpWs->count());
        }

        update(indexOf(tmpWs));
    }
}

void QmlViewManager::pop_back()
{
    m_histogramModel->pop_back();
}

void QmlViewManager::sort()
{
    std::sort(m_histogramModel->begin(), m_histogramModel->end(), [](const auto& lhs, const auto& rhs){
        return lhs->count() > rhs->count();
    });
}

int QmlViewManager::size() const
{
    return m_histogramModel->size();
}

bool QmlViewManager::find(const std::shared_ptr<WordStats>& elem)
{
//    return std::lower_bound(m_histogramModel->begin(), m_histogramModel->end(), elem) == m_histogramModel->end();

    return std::find(m_histogramModel->begin(), m_histogramModel->end(), elem) == m_histogramModel->end();
}

void QmlViewManager::update(int index)
{
    m_histogramModel->update(index);
}

int QmlViewManager::indexOf(const std::shared_ptr<WordStats> &ws)
{
    return m_histogramModel->indexOf(ws);
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
