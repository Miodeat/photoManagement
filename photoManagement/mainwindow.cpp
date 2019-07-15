#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    exif.loadFile(QString("../photoManagement/test.jpg"));
    qDebug()<<"Software"<<exif.DateTimeOriginal.c_str()<<"\t"<<exif.DateTime.c_str()<<"\n";
    qDebug()<<exif.SubSecTimeOriginal.c_str()<<"\n";
    qDebug()<<"ImageWidrh"<<exif.ImageWidth<<"\t"<<exif.ImageHeight<<"\n";
    qDebug()<<"Lat"<<exif.GeoLocation.Latitude<<"  "<<exif.GeoLocation.LatComponents.degrees<<"  "
           <<exif.GeoLocation.LatComponents.minutes<<"  "<<exif.GeoLocation.LatComponents.seconds<<"  "
           <<exif.GeoLocation.LatComponents.direction<<"\n";
    qDebug()<<"Lon"<<exif.GeoLocation.Longitude<<"  "<<exif.GeoLocation.LonComponents.degrees<<"\n";
}

MainWindow::~MainWindow()
{
    delete ui;
}
