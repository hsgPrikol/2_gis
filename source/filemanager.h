#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <iostream>

#include <QDebug>

#include <fstream>
#include <sstream>
#include <thread>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject* parent);

    virtual ~FileManager();

    virtual QStringList readFile(const QString &filepath);



signals:
    void progressUpdated(int);


};

#endif // FILEMANAGER_H
