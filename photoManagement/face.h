#ifndef FACE_H
#define FACE_H
#include <cstdio>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/highgui/highgui.hpp> //简单的界面操作
#include<opencv2/imgproc/imgproc.hpp>  //处理图像的功能，如图像过滤和几何变换
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/objdetect/objdetect_c.h>

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
    void OpenCVgetFaceRectangle(QString filePath);
     void detectAndDisplay(Mat frame);
    int connetNetWork(); //连接网络 使用face++ 否则使用openCV
    //检测人脸用
    CascadeClassifier face_cascade;


private:
    QString Facedescription;
    QString Persion;
    QJsonObject FaceFeature;     //特征点提取
    int FaceID;




};

#endif // FACE_H
