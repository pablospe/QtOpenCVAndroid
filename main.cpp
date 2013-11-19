/*  QML Camera */
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/test_camera/main.qml"));
    viewer.showExpanded();

    return app.exec();
}


/*  Qt C++

#include "mainwindow.h"
#include "videocapture.h"

#include <QApplication>
#include <QCamera>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    QCamera camera;
    VideoCapture viewFinder;
    QWidget window;
    QLabel label;
    QHBoxLayout layout;

    // Create window (by hand, this is an example)
    label.setMinimumWidth(400);
    label.setMinimumHeight(400);
    layout.addWidget(&label);
    window.setLayout(&layout);

    // Set ViewFinder, Camera and Window
    viewFinder.setLabel(&label);
    camera.setViewfinder(&viewFinder);
    camera.setCaptureMode(QCamera::CaptureStillImage);
    window.show();

    // Start Camera
    camera.start();

    return a.exec();
}

*/
