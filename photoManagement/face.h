#ifndef FACE_H
#define FACE_H
#include <cstdio>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc.hpp>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include<QEventLoop>
#include<QTimer>
#include <QObject>
using namespace cv;
#define API_Key (cCGEAS7lBi2U3-kjAEJ6COLTFjEINBGk)
#define API_Secret (t4h0QPufRa9IwYjQnVnYVwCBaj98A0YD)


class Face:public QObject
{
public:
    Face();
    void test();
    int  CompareFormer(); //0为没有入库，1为已经入库
    QJsonObject getFaceFeature(); //联网则使用face++,否则openCv
    void getFaceRectangle();
    int connetNetWork(); //0为没联网 1为联网

private:
    QString Facedescription;
    QString Persion;
    QJsonObject FaceFeature;     //特征点提取
    int FaceID;




};

#endif // FACE_H
