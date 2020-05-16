#include "dbpostgresql.h"
#include <QPoint>


DBPostGreSQL::DBPostGreSQL(easyexif::EXIFInfo *exif)
{

    connectDB();
    this->exif = exif;
    qDebug()<<"进入DBP'o's't'g'reSQL";
    setInsertInfo();


}

QString DBPostGreSQL::toWKT(double lat, double lon)
{
    QString wkt= QString("(%1%2%3)").arg(lat).arg(',').arg(lon);
    //    QString wkt = QString("POINT(%1 %2)").arg(lat).arg(lon);
    qDebug()<<"wkt"<<wkt;
    return wkt;
}

QString DBPostGreSQL::toDate(QString time)
{
    QString year="",month="",day="",hour="",minute="",second="",stime="";
    if(time.size()==0){
        return nullptr;
    }
    QStringList List = time.split(" ");
    QStringList tempList = List[0].split(":");
    if(!tempList.isEmpty()){
        year = tempList[0].trimmed()+"-";
        if(tempList.size()>1){
            month = tempList[1].trimmed()+"-";
            if(tempList.size()>2){
                day = tempList[2].trimmed();
            }
        }
    }
    if(List.size()>1){
        stime = year+month+day+" "+List[List.size()-1];
    }else{
        stime = year+month+day+" 00:00:00";
    }
    qDebug()<<stime;
    return stime;

}

void DBPostGreSQL::connectDB()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setDatabaseName("photoManagement");
    db.setPassword("pj19980806");
    bool ok = db.open();
    if(!ok){
        QMessageBox msgText;
        msgText.setText("数据库连接失败");
        msgText.exec();
        qDebug()<<"error"<<db.lastError();
    }else{
        qDebug()<<"数据库连接成功";
    }
}

bool DBPostGreSQL::commitDB(QSqlQuery &query)
{
    if(query.isActive()){
        db.commit();
        return true;
    }else{
        db.rollback();
        return false;
    }

}

void DBPostGreSQL::insertPhotoInfo()
{
    QSqlQuery query = QSqlQuery(db);

    query.prepare("INSERT INTO photoinfo (photoid, taketime, takeplace, geocoords, photolabel, photopath, facesid) "
                  "VALUES (:photoid, :taketime, :takeplace, :geocoords, :photolabel, :photopath, :facesid)");
    query.bindValue(":photoid", photoInfo.photoId);
    query.bindValue(":taketime", photoInfo.takeTime);
    query.bindValue(":takeplace", QVariant(photoInfo.takePlace));
    query.bindValue(":geocoords", photoInfo.geoCoords);
    query.bindValue(":photolabel", photoInfo.photoLabel);
    query.bindValue(":photopath", QVariant(photoInfo.photoPath));
    query.bindValue(":facesid", photoInfo.facesId);
    query.exec();
    qDebug()<<"photo error:"<<query.lastError();
    commitDB(query);
}

void DBPostGreSQL::insertFaceInfo()
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare("INSERT INTO faceinfo (faceid, facelabel, facepath) "
                  "VALUES (:faceid, :facelabel, :facepath)");
    query.bindValue(":faceid", faceInfo.faceId);
    query.bindValue(":facelabel", faceInfo.faceLabel);
    query.bindValue(":facepath", QVariant(faceInfo.facePath));
    query.exec();
    commitDB(query);
    qDebug()<<"faceInfo error :";
    qDebug()<<query.lastInsertId().toString();
    qDebug()<<query.lastError();

}

int DBPostGreSQL::getPhotoId()
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare("select * from photoinfo");
    query.exec();
    qDebug()<<"lastid is"<<query.size();
    return query.size()+1;
}

int DBPostGreSQL::getFaceId()
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare("select * from faceinfo");
    query.exec();
    qDebug()<<"lastid is"<<query.size();
    return query.size()+1;
}

void DBPostGreSQL::setInsertInfo()
{
    photoInfo.photoId = getPhotoId();
    photoInfo.takeTime =toDate(exif->DateTime.c_str());
    photoInfo.geoCoords = toWKT(exif->GeoLocation.Latitude,exif->GeoLocation.Longitude);
    photoInfo.photoPath = "444";
    photoInfo.photoLabel ="{\"dd\",\"fs\"}";
    photoInfo.takePlace = exif->formattedAdd;
    photoInfo.facesId="{1,2}";
    faceInfo.faceId=1;
    faceInfo.faceLabel="{\"dd\",\"ddd\"}";
    faceInfo.facePath="343434";

}

void DBPostGreSQL::setPhotoPath(QString OphotoPath)
{
    photoInfo.photoPath = OphotoPath;
}

void DBPostGreSQL::startRuKu()
{
    insertFaceInfo();
    insertPhotoInfo();
}

