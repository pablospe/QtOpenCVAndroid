#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T13:15:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
        opencv_tools.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 



#### OpenCV

linux:!android {
    # using pkg-config
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

android {
    # full path to OpenCV Android SDK
    OPENCV_PATH = /home/sppablo/android-src/OpenCV-2.4.7-android-sdk

    INCLUDEPATH += $${OPENCV_PATH}/sdk/native/jni/include/

    LIBS += -L$${OPENCV_PATH}/sdk/native/libs/armeabi-v7a/ \
            -lopencv_androidcamera \
            -lopencv_calib3d \
            -lopencv_contrib \
            -lopencv_core \
            -lopencv_features2d \
            -lopencv_flann \
            -lopencv_highgui \
            -lopencv_imgproc \
            -lopencv_legacy \
            -lopencv_ml \
            -lopencv_objdetect \
            -lopencv_photo \
            -lopencv_stitching \
            -lopencv_ts \
            -lopencv_video \
            -lopencv_videostab

    LIBS += -L$${OPENCV_PATH}/sdk/native/3rdparty/libs/armeabi-v7a \
            -lIlmImf \
            -llibjasper \
            -llibjpeg \
            -llibpng \
            -llibtiff \
            -ltbb
}

RESOURCES += \
    test.qrc
