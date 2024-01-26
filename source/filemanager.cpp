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

        QString tmp;

        for (const QChar &ch : input) {
            if (ch.isLetter()) {
                tmp.append(ch.toLower());
            } else {
                tmp += " ";
            }
        }

        QStringList tokens = tmp.split(" ", Qt::SkipEmptyParts);

        //        qDebug() << tokens;

        return tokens.join(" ");
    };


    auto qt_norm = [](QString filepath){
        if (filepath.isEmpty()) {
            //            qDebug() << "Пустая строка!";
            return QString();
        }

        QString normalizedPath = filepath.mid(7);

        QFileInfo fileInfo(normalizedPath);
        if (!fileInfo.exists()) {
            //            qDebug() << "Некорректный путь или файл не существует!";
            return QString();
        }

        return normalizedPath;
    };

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

        std::cout << "read file " << std::this_thread::get_id() << std::endl;;

        bytes += line.toUtf8().size();

        int percentage = static_cast<int>((static_cast<float>(bytes) / size) * 100);

        emit progressUpdated(percentage);

        //нужна структура данных std::map<string, std::pair<int, int>> где string это имя, первый int это значение, а второй инт, место где он лежит в списке.
        //сделать автообновляемым.На сортировку забить пока.

        //Может быть сейчас в машине уже сделаю это.

        //        std::this_thread::sleep_for(std::chrono::seconds(1));

        QString normalizedLine = qt_ver(line.toStdString().c_str());

        QStringList tm = normalizedLine.split(" ");

        for (const QString& elem : tm) {

            if (elem.isEmpty() || elem == " ") {
                continue;
            }

            lines.push_back(elem);
        }
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
