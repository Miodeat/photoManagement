#ifndef DBPOSTGIS_H
#define DBPOSTGIS_H
#include "exif.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
#include <QVector>
#include <QVariant>
#include <QList>

class dbPostgis:public QObject
{
    Q_OBJECT
public:
    dbPostgis();
    void getExif(easyexif::EXIFInfo exif);
    //connect to database
    void connect();
    void queryTest();
    //transfer data to WKT format
    QString toWKT(double lat,double lon);
    //getting time format can be used to insert into database
    QString toDate(QString time);
    //insert AvatarInfo
    void insertAvatarInfo(QString avatar_label);
    //insert photoInfo
    void insertPhotoInfo(QString label);
    bool commitDB(QSqlQuery& qsQuery);
    //followings are a series of getters and setters
    void setPhotoId();
    int getPhotoId();
    void setTakenTime(QString taken_time);
    QString getTakenTime();
    void setTakenPlace(QString taken_place);
    QString getTakenPlace();
    void setGeocoords(QString geocoords);
    QString getGeocoords();
    void setPhotoLabel(QString photo_label);
    QString getPhotoLabel();
    void setAvatarId();
    int getAvatarId();
    void setAvatarLabel(QString avatar_label);
    QString getAvatarLabel();
    void setPhotoAvatarId(QString photo_avatar_id);
    QString getPhotoAvatarId();
    void setPhotoFilePath(QString filePath);
    QString getFilePath();
    //get an array form str
    QList<QVariant>getArrayFromString(QString str);
    //get str from an array
    QString getStringfromArray(QList<QVariant> array);
    //define photoLabel self
    QList<QVariant> AddphotoLabelSelf(QString label);
//    void queryPhoto();
//    void queryAvatar();
//    void queryPhotoAccordingPhotoLabel(QStringList keyWords);
//    void queryPhotoAccordingTakenTime(QString startTime,QString endTime);
//    void queryPhotoAccordingTakenTimeOrder(QString order);
//    void queryPhotoAccordingPlace(QString place);
//    void updatePhotoLabel(QString photoLabel);
//    void deletePhoto();
    //clear all data;
    void clear();
    QList<QString> getAttributeByPath(QString path, QList<QString> attList);
private:
    QSqlDatabase db;
    QList<int>Aphoto_avatar_id;
    QList<QVariant>Aphoto_label;
    easyexif::EXIFInfo exif;
    struct{
        int photoId;
        QString takenTime;
        QString takenPlace;
        QString photoLabel;
        QString geoCoords;
        QString photoAvatarId;
        QString filePath;
    }photo;
    struct{
        int avatarId;
        QString avatarLabel;
    }avatar;
};

#endif // DBPOSTGIS_H
