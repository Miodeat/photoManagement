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

class AntiGeoCode : public QObject
{
    Q_OBJECT
public:
    AntiGeoCode();
    void callAntiGeoCodeAPI(QString GPSLat, QString GPSLog);

signals:
    void formattedAddReturn(QString);

private slots:
    void finishAntiGeo(QNetworkReply* reply);

private:
    QString degreeToDouble(QString src);
    QString jsonProcessing(QString jsonText);

};

#endif // ANTIGEOCODE_H
