#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "TextMediator.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    TextMediator mediator;
    engine.rootContext()->setContextProperty("textMediator", &mediator);

    using namespace Qt::StringLiterals;
    const QUrl url(u"qrc:/main.qml"_s);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    // Connecting for object creation failure
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // Loading the QML module
    engine.loadFromModule("Lab08", "Main");

    return app.exec();
}

