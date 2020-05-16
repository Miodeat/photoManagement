#ifndef DBPOSTGRESQL_H
#define DBPOSTGRESQL_H
#include "exif.h"
#include <QObject>
#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>

class DBPostGreSQL:public QObject
{
    Q_OBJECT
public:
    DBPostGreSQL(easyexif::EXIFInfo*exif);
public:
    //transfer data to WKT format
    QString toWKT(double lat,double lon);
    //getting time format can be used to insert into database
    QString toDate(QString time);
    void connectDB();
    bool commitDB(QSqlQuery& query);
    void insertPhotoInfo();
    void insertFaceInfo();
    int getPhotoId();
    int getFaceId();
    void setInsertInfo();
    void setPhotoPath(QString OphotoPath);
    void setFacePath(QString facePath);
    void startRuKu();

private:
    struct{
        int photoId;
        QString takePlace;
        QString takeTime;
        QString geoCoords;
        QString photoPath;
        QString photoLabel;
        QString facesId;
    }photoInfo;
    struct{
        int faceId;
        QString faceLabel;
        QString facePath;
    }faceInfo;
private:
    QSqlDatabase db;
    easyexif::EXIFInfo *exif;
};

#endif // DBPOSTGRESQL_H
