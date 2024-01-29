#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QThread>


#include "wordstatsprocessor.h"
#include "qmlviewmanager.h"

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(QObject *parent = nullptr);

    ~ProcessManager();

    QmlViewManager *viewManager() const;
    void setViewManager(QmlViewManager *newViewManager);

public slots:
    void startProcessing(QString filepath);

    void progressUpdate(int value);

    void wordAdded(const QString& word);

private: //methods
    void init();

    void initProcessThread();

private: // fields
    QThread* m_processThread;
    WordStatsProcessor* m_process;
    QmlViewManager* m_viewManager;

    Q_PROPERTY(QmlViewManager *viewManager READ viewManager WRITE setViewManager NOTIFY viewManagerChanged)

signals:

    void viewManagerChanged();
};

#endif // PROCESSMANAGER_H
