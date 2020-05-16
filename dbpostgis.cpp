#include "dbpostgis.h"
#include <QSqlDatabase>
#include <QDebug>
#include "exif.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtCore>
#include <QDate>

dbPostgis::dbPostgis(){

}

void dbPostgis::getExif(easyexif::EXIFInfo exif)
{
    this->exif = exif;
}

void dbPostgis::connect()
{
    db.close();
    //connect to database
    //here you need to change userName and password
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("photoManagement");
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
    qDebug()<<"time is ："<<time;
    QString year="",month="",day="",stime="";
    QStringList tempList = time.split(":");
    if(!tempList.isEmpty()){
        year = tempList[0].trimmed()+"-";
        if(tempList.size()>1){
             month = tempList[1].trimmed()+"-";
             if(tempList.size()>2){
                 day = tempList[2].split(" ")[0].trimmed();

             }
        }
    }
    stime = year+month+day;
    return stime;
}
//insert avatarInfo
void dbPostgis::insertAvatarInfo(QString avatar_label)
{
    setAvatarId();
    setAvatarLabel(avatar_label);
    QSqlQuery query = QSqlQuery(db);
//    query.prepare("INSERT INTO tabl(shape) VALUES(:shape)");
//    query.bindValue(":shape","POINT(112 43)");
    query.prepare("INSERT INTO avatar(avatar_id,avatar_label)"
                  "values(:avatar_id,:avatar_label)");
    query.bindValue(":avatar_id",avatar.avatarId);
    query.bindValue(":avatar_label",avatar.avatarLabel);
    query.exec();
    qDebug()<<"error is"<<query.lastError();
    qDebug()<<"commitDb"<< commitDB(query);

}


//insert photoInfo
void dbPostgis::insertPhotoInfo(QString photo_label)
{
    setPhotoId();
    setTakenTime("");
    setTakenPlace("宿舍");
    setGeocoords(" ");
    setPhotoLabel("漂亮，美丽 ");
    setPhotoAvatarId("1，2");
    setPhotoFilePath("D://file//image");
    QSqlQuery query = QSqlQuery(db);
    qDebug()<<"place:"<<photo.takenPlace;
    query.prepare("INSERT INTO photo(photo_id,taken_time,taken_place,geocoords,photo_label,photo_avatar_id,filepath)"
                  "VALUES(:photo_id,:taken_time,:taken_place,:shape,:photo_label,:photo_avatar_id,:filepath)");
    query.bindValue(":photo_id",photo.photoId);
    query.bindValue(":taken_time",photo.takenTime);
    query.bindValue(":taken_place",photo.takenPlace);
    query.bindValue(":shape",photo.geoCoords);
    query.bindValue(":photo_label",photo.photoLabel);
    query.bindValue(":photo_avatar_id",photo.photoAvatarId
                    );
    query.bindValue(":filepath",photo.filePath);

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

void dbPostgis::setPhotoId()
{
    int counts = 0;
    QSqlQuery query = QSqlQuery(db);
    query.prepare("select * from photo");
    query.exec();
    while(query.next()){

        counts++;
    }
    this->photo.photoId =counts+1;

}

int dbPostgis::getPhotoId()
{
    return photo.photoId;
}

void dbPostgis::setTakenTime(QString taken_time)
{
    taken_time = toDate(exif.DateTime.c_str());
    this->photo.takenTime = taken_time;
}

QString dbPostgis::getTakenTime()
{
    return photo.takenTime;
}

void dbPostgis::setTakenPlace(QString taken_place)
{
    //taken_place = exif.formattedAdd;
    this->photo.takenPlace = taken_place;
}

QString dbPostgis::getTakenPlace()
{
    return photo.takenPlace;
}

void dbPostgis::setGeocoords(QString geocoords)
{
    geocoords = toWKT(exif.GeoLocation.Latitude,exif.GeoLocation.Longitude);
    this->photo.geoCoords = geocoords;

}

QString dbPostgis::getGeocoords()
{
    return photo.geoCoords;
}

void dbPostgis::setPhotoLabel(QString photo_label)
{
    this->photo.photoLabel = photo_label;

}

QString dbPostgis::getPhotoLabel()
{
    return photo.photoLabel;

}


void dbPostgis::setAvatarId()
{
    int counts = 0;
    QSqlQuery query = QSqlQuery(db);
    query.prepare("select * from avatar ");
    query.exec();
    while(query.next()){
        qDebug()<<query.value(0);
        counts++;
    }
    qDebug()<<counts;
    this->avatar.avatarId = counts+1;
}



int dbPostgis::getAvatarId()
{
    return avatar.avatarId;
}

void dbPostgis::setAvatarLabel(QString avatar_label)
{
    this->avatar.avatarLabel = avatar_label;
}

QString dbPostgis::getAvatarLabel()
{
    return avatar.avatarLabel;
}

void dbPostgis::setPhotoAvatarId(QString photo_avatar_id)
{
    this->photo.photoAvatarId = photo_avatar_id;
}

QString dbPostgis::getPhotoAvatarId()
{
    return photo.photoAvatarId;
}

void dbPostgis::setPhotoFilePath(QString filePath)
{
    this->photo.filePath = filePath;
}

QString dbPostgis::getFilePath()
{
    return this->photo.filePath;
}

QList<QVariant> dbPostgis::getArrayFromString(QString str)
{
    QList<QVariant>temp ;
    QStringList templist = str.split(",");
    if(!templist.isEmpty()){
        for(int i = 0;i<templist.size();i++){
            temp[i] = templist[i];
        }
    }
    return temp;
}


QString dbPostgis::getStringfromArray(QList<QVariant> array)
{
    QString str ="";
    if(!array.isEmpty()){
        for(int i = 0;i<array.size();i++){
            str =str+array[i].toString();
        }
    }
    return str;
}

QList<QVariant> dbPostgis::AddphotoLabelSelf(QString label)
{
    Aphoto_label.append(label);
    return Aphoto_label;
}

//void dbPostgis::queryPhoto()
//{
//    QSqlQuery query = QSqlQuery(db);
//    query.prepare("SELECT photo_id,taken_time,taken_place,geocoords,photo_label,photo_avatar_id FROM photo");
//    query.exec();
//    qDebug()<<"query next"<<query.next();
//    while(query.next()){
//        qDebug()<<"photoInfo "<<query.value(0).toInt()<<"  "<<query.value(1).toString()
//               <<" "<<query.value(2).toString()<<" "<<query.value(3).toString()
//              <<" "<<query.value(4).toStringList()<<" "<<query.value(5).toStringList();
//    }
//}

//void dbPostgis::queryAvatar()
//{
//    QSqlQuery query = QSqlQuery(db);
//    query.prepare("SELECT avatar_id,avatar_label FROM avatar");
//    query.exec();
//    while(query.next()){
//        qDebug()<<query.value(0).toInt()<<" "<<query.value(1).toString();
//    }
//}

//void dbPostgis::queryPhotoAccordingPhotoLabel(QStringList keyWords)
//{
//    QSqlQuery query = QSqlQuery(db);
//    query.prepare("select st_astext(geocoords) from photo where photo_id = 1 ");
//    query.exec();
//    while(query.next()){
//        qDebug()<<"id = 1"<<query.value(0).toString();
//    }


//}

//void dbPostgis::queryPhotoAccordingTakenTime(QString startTime, QString endTime)
//{
//    QSqlQuery query = QSqlQuery(db);
//    QString text = "select * from photo where taken_time between "+startTime+" and "+endTime;
//    query.prepare(text);
//    query.exec();
//    while(query.next()){
//       qDebug()<<"some info";
//    }

//}

//void dbPostgis::queryPhotoAccordingTakenTimeOrder(QString order)
//{
//    QString text = "select * from photo order by "+order;
//    QSqlQuery query = QSqlQuery(db);
//    query.prepare(text);
//    query.exec();
//    while (query.next()) {
//        qDebug()<<"some info....";
//    }
//}
////"没写完呢"
//void dbPostgis::queryPhotoAccordingPlace(QString place)
//{
//    QString text = "select path from photo where ST_distance(the_geom:)";
//    QSqlQuery query = QSqlQuery(db);
//    query.prepare(text);

//    query.exec();
//}

//void dbPostgis::updatePhotoLabel(QString photoLabel)
//{
//    Aphoto_label.append(photoLabel);
//    photo.photoLabel = getStringfromArray(Aphoto_label);
//    QString text = "update photo set photo_label =  " +photo.photoLabel +" where photo_id = "+photo.photoId;
//    QSqlQuery query = QSqlQuery(db);
//    query.prepare(text);
//    query.bindValue(":photo_label",photo.photoLabel);
//    query.exec();
//    commitDB(query);
//    while(query.next()){
//        qDebug()<<"some info..";
//    }

//}

//void dbPostgis::deletePhoto()
//{
//    QSqlQuery query = QSqlQuery(db);
//    QString text = "delete from photo where id = "+photo.photoId;
//    query.prepare(text);
//    query.bindValue(":photo_id",photo.photoId);
//    query.exec();
//    commitDB(query);
//}

void dbPostgis::clear()
{
    photo.photoId = 0;
    photo.geoCoords = "";
    photo.takenTime = "";
    photo.takenPlace = "";
    photo.photoAvatarId = "";
    photo.photoLabel = "";
    avatar.avatarId = 0;
    avatar.avatarLabel = "";
    Aphoto_label = {};
    Aphoto_avatar_id ={};

}

QList<QString> dbPostgis::getAttributeByPath(QString path, QList<QString> attList)
{
    QSqlQuery query(db);
    QList<QString>::iterator it = attList.begin();
    // orgnize statement
    QString statementSel = "select ";
    QString statementFrom = " from photo where filepath = '" + path + "'";
    while (it != --attList.end()){
        statementSel += *it + ",";
        it++;
    }
    statementSel += *it;
    QString statement = statementSel + statementFrom;
    query.prepare(statement);
    query.exec();

    QList<QString> result;
    int count = 0;
    while (query.next()) {
        result.push_back(query.value(count).toString());
        count++;
    }

    return result;
}


