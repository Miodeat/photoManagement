#-------------------------------------------------
#
# Project created by QtCreator 2019-07-12T10:32:18
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       +=widgets
QT       += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photoManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        facetagdialog.cpp \
        dbpostgresql.cpp \
        main.cpp \
        antigeocode.cpp \
        exif.cpp \
        dbpostgis.cpp \
        face.cpp \
        mainwindow.cpp \
        photodialog.cpp \
        searchpannel.cpp \
        searchresultdialog.cpp \
        visualize.cpp

HEADERS += \
        facetagdialog.h \
        dbpostgresql.h \
        mainwindow.h \
        antigeocode.h \
        exif.h \
        dbpostgis.h \
        face.h \
        photodialog.h \
        searchpannel.h \
        searchresultdialog.h \
        visualize.h

FORMS += \
        facetagdialog.ui \
        mainwindow.ui \
        photodialog.ui \
        searchpannel.ui \
        searchresultdialog.ui \
        visualize.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc
INCLUDEPATH += opencv2/include
LIBS += -L$$PWD/opencv/lib/ -llibopencv_highgui410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_imgcodecs410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_imgproc410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_objdetect410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_calib3d410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_ccalib410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_core410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_photo410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_video410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_videoio410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_face410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_aruco410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_datasets410.dll
LIBS += -L$$PWD/opencv/lib/ -llibopencv_flann410.dll
INCLUDEPATH += $$PWD/opencv/include
DEPENDPATH += $$PWD/opencv/include


