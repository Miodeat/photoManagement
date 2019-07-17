#ifndef DBPOSTGIS_H
#define DBPOSTGIS_H
#include "exif.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
class dbPostgis:public QObject
{
    Q_OBJECT
public:
    dbPostgis();
    void connect();
    void queryTest();
    QString toWKT(double lat,double lon);
    QString toDate(QString time);
    void insertAvatarInfo(int avatar_id,QString avatar_label);
    void insertPhotoInfo(int photo_id,QString taken_time,QString taken_place,QString geoCoords,QString label,int avatar_id);
    bool commitDB(QSqlQuery& qsQuery);
private:
    QSqlDatabase db;
};

#endif // DBPOSTGIS_H
