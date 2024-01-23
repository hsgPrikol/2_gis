#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QTextStream>
#include <QFile>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject* parent);

    virtual ~FileManager();

    virtual QStringList readFile(const QString& filepath);

signals:
    void progressUpdated(size_t);
};

#endif // FILEMANAGER_H
