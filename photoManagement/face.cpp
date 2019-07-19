#include "face.h"
#include<QObject>
Face::Face()
{

}

void Face::test()
{
    printf("Hello Open CV!");

        Mat img = imread("../photoManagement/test.jpg");  //这个图片需要自己准备，放在project目录下，或者直接写绝对路径
        imshow("test", img);//显示图片6秒
        waitKey(6000);


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
    QNetworkReply *pReply = netAccMana.get(request);


    QTimer timer;
    timer.setInterval(10000);  // 设置超时时间 10 秒
    timer.setSingleShot(true);
    QEventLoop loop;

    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();

}
