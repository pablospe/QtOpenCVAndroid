/*  QML Camera */
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include "mainwindow.h"
#include "videocapture.h"
#include <QApplication>

#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlProperty>

#include <QCamera>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl::fromLocalFile("qml/test_camera/main.qml"));

    QObject *object = component.create();
    qDebug() << "object: " << object;

    QObject *cameraObject = object->findChild<QObject*>("cameraObject");
    qDebug() << "cameraObject: " << cameraObject;

    QVariant cameraVariant = cameraObject->property("mediaObject");
    QCamera *camera = qvariant_cast<QCamera*>(cameraVariant);
    qDebug() << "camera: " << camera;


    VideoCapture viewFinder;
    camera->setViewfinder(&viewFinder);



//    QQuickView view;
//    view.setSource(QUrl::fromLocalFile("qml/test_camera/main.qml"));
//    view.show();
////    QQmlEngine *engine = view.engine();


    return app.exec();
}



//// with C++
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QCamera *camera = new QCamera;
//    VideoCapture viewFinder;
//    camera->setViewfinder(&viewFinder);
//    camera->start();
//    return a.exec();
//}
