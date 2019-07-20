#include "face.h"

#include<QObject>
using namespace std;
Face::Face()
{

}

void Face::test()
{
    qDebug()<<("Hello Open CV!");
    QString filepath="../photoManagement/hezhao2.jpg";
    OpenCVgetFaceRectangle(filepath);


}

QJsonObject Face::getFaceFeature(){

}

int Face::connetNetWork(){
    QNetworkAccessManager netAccMana;
    QString urlString = "https://www.faceplusplus.com.cn/";
    QUrl url(urlString + "user/get");
    qDebug() <<url<<'\n';
    QNetworkRequest request(url); // use url to build a request object
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json;charset=utf-8")); // set request header
    QTimer timer;
    timer.setInterval(8000); // 设置超时时间 8 秒
    timer.setSingleShot(true); // 单次触发
    QNetworkReply *pReply = netAccMana.get(request);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();  //loop循环
    if (timer.isActive()){
        timer.stop();//此时 QNetworkReply::finished，响应完成，还尚未超时
        if (pReply->error() != QNetworkReply::NoError) {
            qDebug() << "使用openCV : ";
        }else {   //7.20号再 写满
            qDebug() << "使用face++ : ";
        }
    }else { //超过5秒
        disconnect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        pReply->abort();
        pReply->deleteLater();
        qDebug() << "使用openCV : ";

    }

}

//之后也可以mainwindow里面加arraylist<filepath> 再写一个函数
void Face::OpenCVgetFaceRectangle(QString filePath){
   std::string  filepath =filePath.toStdString();
    Mat image=imread(filepath);
    if(!image.data){
        qDebug() <<("openCV did not find the photo");
        return;
    }
    qDebug() <<("find the photo,start openCV ");
    detectAndDisplay(image);
    return;
}

void Face::detectAndDisplay(Mat frame){
    if (!face_cascade.load("../photoManagement/opencv/data/haarcascades_cuda/haarcascade_frontalface_alt.xml"))
    {
        qDebug() <<("--(!)Error loading face cascade\n");
        return ;
    }

    std::vector<Rect> faces;
    int scale=1;
    Mat frame_gray;
    cvtColor(frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray ); //直方图均衡化  void equalizeHist(InputArray_src, OutputArray dst)
     //void CascadeClassifier::detectMultiScale( const Mat& image, vector<Rect>& objects,
     //double scaleFactor, int minNeighbors,int flags, Size minObjectSize, Size maxObjectSize)
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, 0 );
      qDebug() <<faces.size();
    //画脸
      // 定义7种颜色，用于标记人脸
        Scalar colors[] =
        {
            // 红橙黄绿青蓝紫
            CV_RGB(255, 0, 0),
            CV_RGB(255, 97, 0),
            CV_RGB(255, 255, 0),
            CV_RGB(0, 255, 0),
            CV_RGB(0, 255, 255),
            CV_RGB(0, 0, 255),
            CV_RGB(160, 32, 240)
        };
    for (int i = 0; i < faces.size();i++)
        {
            Point  center;
            int radius;
            center.x = cvRound((faces[i].x + faces[i].width * 0.5));
            center.y = cvRound((faces[i].y + faces[i].height * 0.5));

            radius = cvRound((faces[i].width + faces[i].height) * 0.3);
            circle(frame, center, radius, colors[i % 7], 1.5);
        }

    imshow("OpenCv Face Detection",frame);
    waitKey(0);
    return ;

}
