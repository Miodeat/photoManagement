#ifndef ANTIGEOCODE_H
#define ANTIGEOCODE_H

#include <QString>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "exif.h"

class AntiGeoCode : public QObject
{
    Q_OBJECT
public:
    AntiGeoCode(easyexif::EXIFInfo* exif);
    void callAntiGeoCodeAPI(double lat, double lon);

signals:
    void slotFinished(QString add);

private:
    QString degreeToDouble(QString src);
    QString jsonProcessing(QString jsonText);
    void finishAntiGeo(QNetworkReply* reply);
    easyexif::EXIFInfo* exif;

};

#endif // ANTIGEOCODE_H
