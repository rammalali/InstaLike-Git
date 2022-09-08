#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlContext>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "imageprocessor.h"
#include "jsonates.h"
#include  <QtQuick/QQuickView>

int main(int argc, char *argv[])
{
    qmlRegisterType<ImageProcessor>("ImageProcessor", 1, 0, "ImageProcessor");

    qputenv("QML_XHR_ALLOW_FILE_READ", QByteArray("1"));

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ImageProcessor img;
    JSONates json;

    auto root_context = engine.rootContext();
    root_context->setContextProperty("Proc", QVariant::fromValue(&img));
    root_context->setContextProperty("jayson", QVariant::fromValue(&json));


    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    return app.exec();
}
