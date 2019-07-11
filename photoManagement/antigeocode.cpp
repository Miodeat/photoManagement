#include "antigeocode.h"



AntiGeoCode::AntiGeoCode()
{

}

void AntiGeoCode::callAntiGeoCodeAPI(QString GPSLat, QString GPSLog)
{
    QNetworkAccessManager* netAccMana = new QNetworkAccessManager();

    // turn latitute and longitute form degree to decimalism
    QString lat = degreeToDouble(GPSLat);
    QString log = degreeToDouble(GPSLog);

    connect(netAccMana, &QNetworkAccessManager::finished, this, &AntiGeoCode::finishAntiGeo);

    // set url
    QString urlString = "https://api.map.baidu.com/geocoder/v2/?ak=AmgZttBtRXOEY7R9pkC1ScETpDUKlVef&location="
                    + lat +"," + log + "&output=json&pois=1";
    QUrl url(urlString + "user/get");

    QNetworkRequest request(url); // use url to build a request object
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json;charset=utf-8")); // set request header
    netAccMana->get(request); // invoke api by using "get" method
}


void AntiGeoCode::finishAntiGeo(QNetworkReply* reply)
{    
    int isError = reply->error();
    if(isError == QNetworkReply::NoError){
        QByteArray data = reply->readAll(); // get reply
        QString datastr = QString::fromUtf8(data);
        QString formattedAdd = jsonProcessing(datastr); // get formatted address form reply
        emit formattedAddReturn(formattedAdd); // emit signal
    }
    else{
       qDebug() << "Error code: " << isError << "\n";

    }
    reply->deleteLater();
}

QString AntiGeoCode::degreeToDouble(QString src)
{
    QStringList tempList = src.split("°");
    double du = tempList[0].trimmed().toDouble();
    tempList = tempList[1].split("'");
    double fen = tempList[0].trimmed().toDouble();
    double miao = tempList[1].split("\"")[0].trimmed().toDouble();
    double result = du + fen / 60 + miao / 3600;
    return QString::number(result);
}

QString AntiGeoCode::jsonProcessing(QString jsonText)
{
    QJsonDocument jsDoc = QJsonDocument::fromJson(jsonText.toUtf8());
    QJsonObject jsOb = jsDoc.object();
    QJsonObject resultOb = jsOb.value("result").toObject();
    QString forAdd = resultOb.value("formatted_address").toString();
    return forAdd;
}
