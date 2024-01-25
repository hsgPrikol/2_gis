#ifndef QMLVIEWMANAGER_H
#define QMLVIEWMANAGER_H

#include <QObject>

#include "wordstatsmodel.h"
#include "sortfiltermodel.h"

class QmlViewManager : public QObject
{
    Q_OBJECT
public:
    explicit QmlViewManager(QObject *parent = nullptr);

    ~QmlViewManager();

    int maxWordCount() const;
    void setMaxWordCount(int newMaxWordCount);

    int maxRepeatedWord() const;
    void setMaxRepeatedWord(int newMaxRepeatedWord);

    WordStatsModel *histogramModel() const;
    void setHistogramModel(WordStatsModel *newHistogramModel);

    SortFilterModel *proxyModel() const;
    void setProxyModel(SortFilterModel *newProxyModel);

    int processValue() const;
    void setProcessValue(int newProcessValue);

    Q_INVOKABLE void add(const QString &word, int count);

    Q_INVOKABLE void add(const std::shared_ptr<WordStats>& ws);

    void pop_back();

    void sort();

    Q_INVOKABLE int size() const;

    bool find(const std::shared_ptr<WordStats>& elem);

    void update(int index);

    int indexOf(const std::shared_ptr<WordStats>& ws);

public slots:
    void progress(int value);

private: //methods
    void init();

    void initProxy();

private: //fields
    int m_maxWordCount;

    int m_maxRepeatedWord;

    int m_processValue;

    WordStatsModel* m_histogramModel;

    SortFilterModel* m_proxyModel;

    Q_PROPERTY(int maxWordCount READ maxWordCount WRITE setMaxWordCount NOTIFY maxWordCountChanged)

    Q_PROPERTY(int maxRepeatedWord READ maxRepeatedWord WRITE setMaxRepeatedWord NOTIFY maxRepeatedWordChanged)

    Q_PROPERTY(WordStatsModel *histogramModel READ histogramModel WRITE setHistogramModel NOTIFY histogramModelChanged)

    Q_PROPERTY(SortFilterModel *proxyModel READ proxyModel WRITE setProxyModel NOTIFY proxyModelChanged)

    Q_PROPERTY(int processValue READ processValue WRITE setProcessValue NOTIFY processValueChanged)

signals:
    void maxWordCountChanged();
    void maxRepeatedWordChanged();
    void histogramModelChanged();
    void proxyModelChanged();
    void processValueChanged();
};

#endif // QMLVIEWMANAGER_H
