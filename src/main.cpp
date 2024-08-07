#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "appcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    AppController appController;
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("cryptoCurrencyModel", appController.model());
    engine.rootContext()->setContextProperty("appController", &appController);
    engine.loadFromModule("currencyApp", "Main");

    return app.exec();
}
