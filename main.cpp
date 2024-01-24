//#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

#include "model.h"
//#include "wordstatsmodel.h"

#include "wordstatsprocessor.h"

//#include <QtCharts>

#define MODEL_ORG "Model.org"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

//    QChartView *chart = new QChartView;

    QQmlApplicationEngine engine;

    qmlRegisterType<Model>(MODEL_ORG, 1, 0, "Md");
    qmlRegisterType<Model>(MODEL_ORG, 1, 0, "WordStatsModel");

//    WordStatsModel wsModel;
    WordStatsProcessor wsModel;

    engine.rootContext()->setContextProperty("_wsModel", &wsModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
