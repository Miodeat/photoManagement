#include "myface.h"
#include <QString>
#include <QVector>
#include <vector>
#include <QDebug>
#include <iostream>
using namespace std;

myFace::myFace()
{

    Mat img = imread("../photoManagement/test.jpg");
    qDebug()<<"img.size"<<img.size<<"\n";
}

void myFace::test()
{
    string xpath = "../photoManagement/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml";

    CascadeClassifier ccf;
    Mat img = imread("../photoManagement/test.jpg");
   // Mat img = imread("F:/opencv/sources/samples/data/pca_test1.jpg");

    //imshow("input image",img);
//    Mat gray ,binary;
//    cvtColor(img,gray,COLOR_BGR2RGB);
//    //threshold(gray,binary,0,255,THRESH_BINARY|THRESH_OTSU);
//    //imshow("binary image",binary);
//    vector<Vec4i> hireachy;
//    vector <vector<Point>> contours;
//    findContours(img,contours,hireachy,RETR_LIST,CHAIN_APPROX_NONE);
//    //Mat results = img.clone();
//    for(int i = 0;i < contours.size();i++){
//        drawContours(img,contours,i,Scalar(0,0,255),2,8);
//    }
//    imshow("contours image",img);
//    waitKey(0);
     if(!ccf.load(xpath)){
        cout<<"不能加载指定的xml文件";
    }
    vector <Rect> faces;
    Mat gray;
    cvtColor(img,gray,CV_BGR2GRAY);
    equalizeHist(gray,gray);
    ccf.detectMultiScale(gray,faces,1.1,3,0,Size(10,10),Size(50,50));
    for(vector<Rect>::const_iterator iter=faces.begin();iter!=faces.end();iter++){
         rectangle(img,*iter,Scalar(0,0,255),2,8);

     }
     imshow("faces",img);
     qDebug()<<"imshow";
     waitKey(6000);
}

void myFace::test2()
{
    VideoCapture capture(0);
    if(!capture.isOpened()){
        qDebug()<<"could not open the camera";
    }
//    Size S = Size((int)capture.get(CV_))
}
