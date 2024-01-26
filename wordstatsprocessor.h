#ifndef WORDSTATSPROCESSOR_H
#define WORDSTATSPROCESSOR_H

#include <QObject>
#include <QThread>

#include "filemanager.h"

class WordStatsProcessor : public QObject
{
    Q_OBJECT
public:
    explicit WordStatsProcessor(QObject *parent = nullptr);

    ~WordStatsProcessor();

    const QString &filepath() const;
    void setFilepath(const QString &newFilepath);

public slots:
    void startProcessing();

private: //methods
    QString m_filepath;

private: // fields
    std::unique_ptr<FileManager> m_fileManager;

signals:

    void dataChanged(int index);

    void newWordProcessed(const QString& word);
};

#endif // WORDSTATSPROCESSOR_H
