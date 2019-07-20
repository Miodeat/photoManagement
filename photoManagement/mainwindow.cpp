#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlDriverCreator>
#include <QSqlQuery>
#include <QMessageBox>
#include"face.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // exif.loadFile(QString("../photoManagement/test.jpg"));
//    db.connect();
//    db.queryTest();
//    QString geoCoords = db.toWKT(exif.GeoLocation.Latitude,exif.GeoLocation.Longitude);
//    QString avatar_label("向日葵");
//    QString photo_label("穿暖花开");
//    db.insertAvatarInfo(6,avatar_label);
//    db.insertPhotoInfo(4,db.toDate(exif.DateTimeOriginal.c_str()),"中北大学",geoCoords,photo_label,
//                       3);
    Face face;
    face.test();
}

MainWindow::~MainWindow()
{
    delete ui;
}
