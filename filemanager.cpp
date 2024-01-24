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
    auto normalizeString = [](const std::string& input) {
        std::string result;
        std::istringstream stream(input);
        std::string token;

        while (stream >> token) {
            result += token + " ";
        }

        if (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }

        return result;
    };

    auto normalizeFilepath = [](const std::string& filePath){
        std::string newFilr = filePath;
        if (newFilr.size() >= 7/* && newFilePath.substr(0, 7) == "file://"*/)
        {
            newFilr.erase(0, 7);
        }
        return newFilr;
    };


    auto qt_ver = [](const QString& input) {
        QStringList tokens = input.split(" ", Qt::SkipEmptyParts);
        return tokens.join(" ");
    };


    auto qt_norm = [](QString filepath){
        if (filepath.isEmpty()) {
            qDebug() << "Пустая строка!";
            return QString();
        }

        QString normalizedPath = filepath.mid(7);

        QFileInfo fileInfo(filepath);
        if (!fileInfo.exists()) {
            qDebug() << "Некорректный путь или файл не существует!";
            return QString();
        }

        return normalizedPath;
    };

    qDebug() << filepath;

    QFile file(filepath.mid(7));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл!";
        return QStringList();
    }

    QStringList lines;

    int size = file.size();
    int bytes = 0;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        bytes += line.toUtf8().size();

        int percentage = static_cast<int>((static_cast<float>(bytes) / size) * 100);

        emit progressUpdated(percentage);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        QString normalizedLine = qt_ver(line.toStdString().c_str());

        lines.push_back(normalizedLine);
    }

    emit progressUpdated(100);
    file.close();
    return lines;
















    //    if (filepath.isNull() || filepath.isEmpty()) {
    //        qDebug() << "isEmpty";
    //        return QStringList();
    //    }
    //    std::string str = filepath.toStdString();

    //    if (str.size() >= 7) {
    //        str.erase(0, 7);
    //    }
    //    //    std::string newFilePath = normalizeFilepath(filepath.toStdString());

    //    std::ifstream inputFile(str);

    //    if (!inputFile.is_open()) {
    //        qDebug() << "Не удалось открыть файл!";
    //        return QStringList();
    //    }

    //    QStringList lines;

    //    std::string line;
    //    while (std::getline(inputFile, line)) {

    //        std::string normalizedLine = normalizeString(line);

    //        lines.push_back(QString::fromStdString(normalizedLine));
    //    }

    //    inputFile.close();
    //    return lines;
}
