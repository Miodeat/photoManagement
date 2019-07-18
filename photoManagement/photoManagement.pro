#-------------------------------------------------
#
# Project created by QtCreator 2019-07-12T10:32:18
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

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

INCLUDEPATH+= ./opencv/include\
              ./opencv/include/opencv\
              ./opencv/include/opencv2


LIBS+=-L./oepncv/lib/.*-l
#LIBS+=-L./opencv/lib/ -llibopencv_core310\
#      -L./opencv/lib/ -llibopencv_calib3d310\
#      -L./opencv/lib/ -llibopencv_photo310\
#      -L./opencv/lib/-llibopencv_imgcodecs310\
#      -L./opencv/lib/-llibopencv_imgproc310\
#      -L./opencv/lib/-llibopencv_shape310\
#      -L./opencv/lib/-llibopencv_highgui310
#      -L./oepncv/lib/-llibopencv_features2d310


SOURCES += \
        antigeocode.cpp \
        dbpostgis.cpp \
        exif.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        antigeocode.h \
        dbpostgis.h \
        exif.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
