#ifndef WORDSTATSPROCESSOR_H
#define WORDSTATSPROCESSOR_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <algorithm>
#include <exception>
#include <unordered_map>


#include <thread>

#include "filemanager.h"
#include "wordstatsmodel.h"
#include "wordcounter.h"
#include "sortfiltermodel.h"
#include "progressbarprocess.h"
#include "qmlviewmanager.h"

class WordStatsProcessor : public QObject
{
    Q_OBJECT
public:
    explicit WordStatsProcessor(QObject *parent = nullptr);

    ~WordStatsProcessor();

    Q_INVOKABLE void processFile(const QString &filePath);

    Q_INVOKABLE void addObject();

    QmlViewManager *viewManager() const;
    void setViewManager(QmlViewManager *newViewManager);

private: //methods


private: // fields
    std::unique_ptr<FileManager> m_fileManager;

    QmlViewManager* m_viewManager;

    Q_PROPERTY(QmlViewManager *viewManager READ viewManager WRITE setViewManager NOTIFY viewManagerChanged)

signals:
    void viewManagerChanged();
};

#endif // WORDSTATSPROCESSOR_H
