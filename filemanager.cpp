#include "filemanager.h"

FileManager::FileManager(QObject *parent)
    : QObject(parent)
{

}

FileManager::~FileManager()
{

}

QStringList FileManager::readFile(const QString& filepath)
{
    QFile file(filepath);

    if (!file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        // maybe call throw
        return QStringList();
    }

    QTextStream stream(&file);

    QStringList list;

    size_t fileSize = file.size();

    size_t bytesRead = 0u;

    while (!stream.atEnd()) {
        QString tmp = stream.readLine();
        bytesRead += tmp.size();
        list.push_back(stream.readLine());

        size_t percentage = static_cast<size_t>((static_cast<float>(bytesRead) / fileSize) * 100);
        emit progressUpdated(percentage);
    }

    file.close();

    return list;
}
