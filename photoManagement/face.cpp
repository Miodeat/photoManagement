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
