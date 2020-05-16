#ifndef FACE_H
#define FACE_H
#include <cstdio>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include<opencv2/cxcore.h>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QHttpPart>
#include <QEventLoop>
#include <QTimer>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/highgui/highgui.hpp> //简单的界面操作
#include<opencv2/imgproc/imgproc.hpp>  //处理图像的功能，如图像过滤和几何变换
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/objdetect/objdetect_c.h>
#include <opencv2/opencv.hpp>
#include <QObject>
#include <stdio.h>
#include <QString>
#include "dbpostgis.h"
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QPushButton>
#include <QLabel>
#include <string>
#include <vector>
#include <QFile>
#include <opencv/cv.h>
using namespace cv;
using namespace std;
class Face : public QObject
{
    Q_OBJECT
public:
    Face();

    void test();
    int  CompareFormer(); //0为没有入库，1为已经入库
    QJsonObject getFaceFeature(); //联网则使用face++,否则openCv
    void OpenCVgetFaceRectangle(QString filePath);
    void detectAndDisplay(QString filePath,Mat frame);
    int connetNetWork(); //连接网络 使用face++ 否则使用openCV
    QHttpPart setHttpPart(QByteArray body,QVariant value);//used in face++ to set params
    QHttpPart imageHttpPart(const QString &filename,QVariant value);//used in face++ to set params
    QHttpMultiPart* setKeyAndSecret();
    //检测人脸用
    CascadeClassifier face_cascade;
    void OpenCvfaceCompareConfidence();
    void CompareHist(IplImage* faceImage1,IplImage* faceImage2);
    double getPSNR(const Mat& I1, const Mat& I2);      // CPU versions
    Scalar getMSSIM( const Mat& I1, const Mat& I2);
    IplImage* detect( Mat& img, CascadeClassifier& cascade);
    void test2();
    void createFaceSet(QString displayName,QString outerId);
    QList<QString> getfaceToken(QByteArray responseData);
    void detectFace(const QString &filename);
    //used to get
    void setMaxConfidence(QString face_token,double confidence);
    void addFaceTokens(QList<QString>faceTokens);
    //将两个人脸进行比对，来判断是否为同一个人，返回比对结果置信度和不同误识率下的阈值。
    void compareFace(const QString &faceTk1,const QString &faceTk2);
    //在已有的 FaceSet 中找出与目标人脸最相似的一张或多张人脸，返回置信度和不同误识率下的阈值。
    void searchFace(const QString &image);
    void storedInDbOp(const QString &filePath);

    //zw test confidence gap
    void getPilesFaces();
    void CompareFaceHSV();

public slots:
     void finishedQ(QNetworkReply *reply);
     void finishedDetect(QNetworkReply *reply);
     void finishedSearch(QNetworkReply *reply);

     // a slot can recieve tags of faces from FaceTagDialog
     //
     // @param tags: a QList store tags of faces
     // @return
     void finishFaceTagsInput(QList<QString> tags);
public:
    bool getIsError() const;
    void setIsError(bool value);

private:
    QString Facedescription;
    QString Persion;
    QJsonObject FaceFeature;     //特征点提取
    int FaceID;
//    dbPostgis db;
    QNetworkAccessManager *manager;
    QString filename1;
    QString filename2;
    QString apiKey,apiSecret;
    QString faceset_token,outer_id;
    bool isError= false;
    double confidence;// searchApi 中得出的confidence
    QString face_token;//在faceSet中找出的和目标人脸最相思的人脸的face_token

 private:

};

#endif // FACE_H
