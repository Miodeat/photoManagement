#include "mainwindow.h"
#include <QApplication>
#include "exifimg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    ExifImg exif;
    exif.test();
    return a.exec();
}
