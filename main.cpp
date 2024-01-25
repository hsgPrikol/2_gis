//#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QIcon>

#include "wordstatsprocessor.h"

//#include <QtCharts>

#define MODEL_ORG "Model.org"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon("images/logo.png"));

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<WordStatsProcessor>(MODEL_ORG, 1, 0, "WordStatsModel", "");
    qmlRegisterUncreatableType<QmlViewManager>(MODEL_ORG, 1, 0, "ViewManager", "");

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
