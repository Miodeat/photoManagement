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

using namespace cv;


class Face
{
public:
    Face();
    void test();

private:
    QString Facedescription;
    QString Persion;
    QJsonObject FaceFeature;     //特征点提取
    int FaceID;



};

#endif // FACE_H
