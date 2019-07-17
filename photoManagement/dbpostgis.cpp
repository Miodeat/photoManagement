#include "dbpostgis.h"
#include <QSqlDatabase>
#include <QDebug>
#include "exif.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtCore>
#include <QDate>
#include <QGeometry>
dbPostgis::dbPostgis(){
}

void dbPostgis::connect()
{
    //connect to database
    //here you need to change userName and password
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("photoMangement");
    db.setUserName("postgres");
    db.setPassword("pj19980806");
    bool ok = db.open();
    if(!ok){
        QMessageBox msgText;
        msgText.setText("数据库连接失败");
        msgText.exec();
        qDebug()<<"error"<<db.lastError();
    }

}
//only a test
void dbPostgis::queryTest()
{
   // qDebug()<<db.open();
    QSqlQuery query = QSqlQuery(db);
    QString strText("select * from photo");
    query.prepare(strText);
    query.exec();
    while (query.next()) {
        int photo_id = query.value(0).toInt();
        QDate photo_time = query.value(1).toDate();
        QString taken_place = query.value(2).toString();
        QString geoCoords = query.value(3).toString();
        QString label = query.value(4).toString();
        int avatar_id = query.value(5).toInt();
        qDebug()<<photo_id<<' '<<photo_time<<' '<<taken_place<<' '<<
                  geoCoords<<' '<<label<<avatar_id<<"\n";
    }

}
//convert data to WKT format
QString dbPostgis::toWKT(double lat, double lon)
{

    QString wkt= QString("POINT(%1%2%3)").arg(lat).arg(' ').arg(lon);
    qDebug()<<"wkt"<<wkt;
    return wkt;
}
//convert to standard date
QString dbPostgis::toDate(QString time)
{
    QStringList tempList = time.split(":");
    QString year = tempList[0].trimmed()+"-";
    QString month = tempList[1].trimmed()+"-";
    QString day = tempList[2].split(" ")[0].trimmed();
    QString stime = year+month+day;
    return stime;
}
//insert avatarInfo
void dbPostgis::insertAvatarInfo(int avatar_id, QString avatar_label)
{
    QSqlQuery query = QSqlQuery(db);
//    query.prepare("INSERT INTO tabl(shape) VALUES(:shape)");
//    query.bindValue(":shape","POINT(112 43)");
    query.prepare("INSERT INTO avatar(avatar_id,avatar_label)"
                  "values(:avatar_id,:avatar_label)");
    query.bindValue(":avatar_id",avatar_id);
    query.bindValue(":avatar_label",avatar_label);
    query.exec();
    qDebug()<<"error is"<<query.lastError();
    qDebug()<<"commitDb"<< commitDB(query);

}
//insert photoInfo
void dbPostgis::insertPhotoInfo(int photo_id, QString taken_time, QString taken_place, QString geocoords, QString photo_label, int avatar_id)
{
    qDebug()<<db.open();
    QSqlQuery query = QSqlQuery(db);
    query.prepare("INSERT INTO photo(photo_id,taken_time,taken_place,geocoords,photo_label,avatar_id) VALUES(:photo_id,:taken_time,:taken_place,:shape,:photo_label,:avatar_id)");
    query.bindValue(":photo_id",15);
    query.bindValue(":taken_time","2002-03-03");
    query.bindValue(":taken_place",taken_place);
    query.bindValue(":shape",geocoords);
    query.bindValue(":photo_label",photo_label);
    query.bindValue(":avatar_id",avatar_id);
    query.exec();
    qDebug()<<"error"<<query.lastError();
    qDebug()<<"commitDb"<< commitDB(query);
}
//test whether data was stored
bool dbPostgis::commitDB(QSqlQuery &qsQuery)
{
    if(qsQuery.isActive()){
        db.commit();
        return  true;
    }else{
        db.rollback();
        return false;
    }
}
