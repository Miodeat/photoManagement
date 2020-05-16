#include "face.h"
#include<QObject>
#include <iostream>
#include <QImage>
#include <QBuffer>
#include "facetagdialog.h"
using namespace std;

Face::Face()
{
//    FaceID = db.getAvatarId();
    filename1 = ".\\test.jpg";
    filename2 = ".\\test3.jpg";
    //followings are some keys used in face++ which cann't be modified
    this->apiKey = "IB29o41okBd85lADqKTuOr2dILbikl1E";
    this->apiSecret = "dLOsMaOYPdjeQ5Ir-ifHVR3hDiyeaElm";
    this->faceset_token ="248b8ec876fcd612c3aa25ae4e844f9f";
    this->outer_id ="facesInPhotoManagement";
    confidence = 0.0;
    face_token = "";

}
//this function used as entry point for image recognition

void Face::test()
{
    QList<QString>filenames;
    filenames.push_back(filename1);
    filenames.push_back(filename2);
    //    detectFace(filenames);
    qDebug()<<("Hello Open CV!");
    QString filepath=".\\hezhao1.jpg";
    connetNetWork();
        searchFace(filename1);
//    compareFace(filename1,filename2);
    //    OpenCVgetFaceRectangle(filepath);
    //    createFaceSet("faces","facesInPhotoManagement");

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
            qDebug() << "the error is"<<pReply->error()<<" ,使用openCV : ";
            return 0;
        }else {
            qDebug() << "联网测试成功，使用face++ : ";

        }
    }else { //超过5秒
        disconnect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        pReply->abort();
        pReply->deleteLater();
        qDebug() << "使用openCV : ";

    }
    return 1;

}

QHttpPart Face::setHttpPart(QByteArray body, QVariant value)
{
    QHttpPart part ;
    part.setHeader(QNetworkRequest::ContentDispositionHeader,value);
    part.setBody(body);
    return part;
}

QHttpPart Face::imageHttpPart(const QString &filename, QVariant value)
{

    QHttpPart imagePart ;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,value);
    QImage image(filename);
    QByteArray ba;
    QByteArray hex;
    QBuffer buf(&ba);
    if(buf.open(QIODevice::WriteOnly)){
        image.save(&buf,"jpeg",20);
        hex = ba.toBase64();
        buf.close();
    }else{
        qDebug()<<"buf.error"<<buf.errorString();
    }

    imagePart.setBody(hex);
    return imagePart;

}

QHttpMultiPart* Face::setKeyAndSecret()
{
    QHttpMultiPart *multiPart = new QHttpMultiPart;
    QHttpPart apikey  = setHttpPart(this->apiKey.toLatin1(),QVariant("form-data; name=\"api_key\""));
    QHttpPart apisecret = setHttpPart(this->apiSecret.toLatin1(),QVariant("form-data; name=\"api_secret\""));
    multiPart->append(apikey);
    multiPart->append(apisecret);
    return multiPart;

}

void Face::createFaceSet(QString displayName, QString outerId)
{   QTimer timer;
    timer.setInterval(8000);
    timer.setSingleShot(true);
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart apikey = setHttpPart(this->apiKey.toLatin1(),QVariant("form-data; name=\"api_key\""));
    QHttpPart apisecret = setHttpPart(this->apiSecret.toLatin1(),QVariant("form-data; name=\"api_secret\""));
    multiPart->append(apikey);
    multiPart->append(apisecret);
    if(displayName!=""){
        QHttpPart textPart1;
        textPart1 = setHttpPart(displayName.toLatin1(),QVariant("form-data;name=\"display_name\""));
        multiPart->append(textPart1);
    }
    if(outerId!=""){
        QHttpPart textPart2;
        textPart2 = setHttpPart(outerId.toLatin1(),QVariant("form-data;name=\"outer_id\""));
        multiPart->append(textPart2);
    }
    QUrl url("https://api-cn.faceplusplus.com/facepp/v3/faceset/create");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->post(request, multiPart);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
    if (timer.isActive()){
        timer.stop();
        if (reply->error() != QNetworkReply::NoError) {
            this->isError = true;
            qDebug() << "In  faceSetCreate the error is "<<reply->errorString();
            return ;
        }else {
            this->isError = false;
            qDebug()<<reply->readAll();
        }
    }else { //超过8秒
        disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        reply->abort();
        reply->deleteLater();
        qDebug() << "联网超时";
    }
}

QList<QString> Face::getfaceToken(QByteArray responseData)
{
    QMap<QString,QVariant>map;
    QJsonDocument documment ;
    map = documment.fromJson(responseData).toVariant().toMap();
    if(isError){
        QString errorMsg = map.value("error_message").toString();
        QList<QString>errors;
        errors.push_back(errorMsg);
        return errors;
    }else{
        QJsonArray faces = map.value("faces").toJsonArray();
        QList<QString> faceTokens;
        for(int i = 0;i<faces.size();i++){
            QJsonObject faceObj =faces.at(i).toObject();
            QString faceToken = faceObj.value("face_token").toString();
            faceTokens.push_back(faceToken);
        }
        return faceTokens;

    }
}

void Face::detectFace(const QString &filename)
{
    QTimer timer;
    timer.setInterval(10000);
    timer.setSingleShot(true);
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    if(filename!=""){
        QUrl url("https://api-cn.faceplusplus.com/facepp/v3/detect");
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart apikey = setHttpPart(this->apiKey.toLatin1(),QVariant("form-data; name=\"api_key\""));
        QHttpPart apisecret = setHttpPart(this->apiSecret.toLatin1(),QVariant("form-data; name=\"api_secret\""));
        multiPart->append(apikey);
        multiPart->append(apisecret);
        QString dataform = "form-data; name=\"image_base64\"";
        QHttpPart imagePart = imageHttpPart(filename.toLatin1(),dataform);
        multiPart->append(imagePart);
        QNetworkRequest request(url);
        QNetworkReply *reply = manager->post(request, multiPart);
        multiPart->setParent(reply); // 用 reply 删除 multiPart
        QEventLoop loop;
        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        timer.start();
        loop.exec();  //loop循环
        if (timer.isActive()){
            //此时 QNetworkReply::finished，响应完成，还尚未超时
                timer.stop();
             int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
              if (reply->error() != QNetworkReply::NoError) {
                  this->isError=true;
                  qDebug() << "In detectImage the error is "<<reply->error()<<reply->errorString();
                  return ;
              }else {
                 finishedDetect(reply);
                 this->isError = false;

              }
          }else { //超过8秒
              disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
              reply->abort();
              reply->deleteLater();
              qDebug() << "联网超时";

           }
    }
}

void Face::setMaxConfidence(QString face_token, double confidence)
{
    this->face_token = face_token;
    this->confidence = confidence;
}


void Face::addFaceTokens(QList<QString> faceTokens)
{

    QTimer timer;
    timer.setInterval(8000);
    timer.setSingleShot(true);
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QHttpMultiPart *multiPart = new  QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart apikey,apisecret,faceset_token,face_tokens;
    apikey = setHttpPart(this->apiKey.toLatin1(),QVariant("form-data; name=\"api_key\""));
    apisecret = setHttpPart(this->apiSecret.toLatin1(),QVariant("form-data; name=\"api_secret\""));
    faceset_token = setHttpPart(this->faceset_token.toLatin1(),QVariant("form-data; name=\"faceset_token\""));
    QString facetokenStr="";
    if(faceTokens.size()<1){
        return ;
    }
    for(int i = 0;i<faceTokens.size()-1;i++){
        facetokenStr=facetokenStr+faceTokens[i]+",";
    }
    facetokenStr = facetokenStr+faceTokens[faceTokens.size()-1];
    qDebug()<<"查看facetokemmstr"<<facetokenStr;
    face_tokens = setHttpPart(facetokenStr.toLatin1(),QVariant("form-data; name=\"face_tokens\""));
    multiPart->append(apikey);
    multiPart->append(apisecret);
    multiPart->append(faceset_token);
    multiPart->append(face_tokens);
    QUrl url("https://api-cn.faceplusplus.com/facepp/v3/faceset/addface");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->post(request,multiPart);
    multiPart->setParent(reply); // 用 reply 删除 multiPart
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();  //loop循环
    if (timer.isActive()){
        //此时 QNetworkReply::finished，响应完成，还尚未超时
        timer.stop();
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug()<<"httpCodes"<<statusCode;
        if (reply->error() != QNetworkReply::NoError) {
            this->isError=true;
            qDebug() << "In addFaceToken the error is "<<reply->error()<<reply->errorString();
            return ;
        }else {
            qDebug()<<reply->readAll();
        }
    }else { //超过8秒
        disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        reply->abort();
        reply->deleteLater();
        qDebug() << "联网超时";

    }
    if(reply->error()==QNetworkReply::NoError){
        qDebug()<<"测试加入facetoken"<<reply->readAll();
    }else{
        qDebug()<<"error in AddFaceToken "<<reply->errorString();
    }


}

void Face::compareFace(const QString &faceTk1, const QString &faceTk2)
{
    QTimer timer;
    timer.setInterval(8000);
    timer.setSingleShot(true);
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart apikey,apisecret,face1,face2;
    apikey = setHttpPart(this->apiKey.toLatin1(),QVariant("form-data; name=\"api_key\""));
    apisecret = setHttpPart(this->apiSecret.toLatin1(),QVariant("form-data; name=\"api_secret\""));
    face1 = imageHttpPart(faceTk1.toLatin1(),QVariant("form-data; name=\"image_base64_1\""));
    face2 = imageHttpPart(faceTk2.toLatin1(),QVariant("form-data; name=\"image_base64_2\""));
    multiPart->append(apikey);
    multiPart->append(apisecret);
    multiPart->append(face1);
    multiPart->append(face2);
    QUrl url("https://api-cn.faceplusplus.com/facepp/v3/compare");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->post(request,multiPart);
    multiPart->setParent(reply);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();  //loop循环
    if (timer.isActive()){
        //此时 QNetworkReply::finished，响应完成，还尚未超时
        timer.stop();
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug()<<"httpCodes"<<statusCode;
        if (reply->error() != QNetworkReply::NoError) {
            this->isError=true;
            qDebug() << "In compareFace the error is "<<reply->error()<<reply->errorString();
            return ;
        }else {
            isError= false;
            finishedSearch(reply);
        }
    }else { //超过8秒
        disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        reply->abort();
        reply->deleteLater();
        qDebug() << "联网超时";
    }
}

void Face::searchFace(const QString &image)
{
    QTimer timer;
    timer.setInterval(8000);
    timer.setSingleShot(true);
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    connect(manager,&QNetworkAccessManager::finished,this,&Face::finishedSearch);
    QHttpMultiPart * multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart apikey,apisecret,targetImg,faceset;
    apikey = setHttpPart(this->apiKey.toLatin1(),QVariant("form-data; name=\"api_key\""));
    apisecret = setHttpPart(this->apiSecret.toLatin1(),QVariant("form-data'; name=\"api_secret\""));
    targetImg = setHttpPart(image.toLatin1(),QVariant("form-data; name=\"face_token\""));
    faceset = setHttpPart(this->faceset_token.toLatin1(),QVariant("form-data; name=\"faceset_token\""));
    multiPart->append(apikey);
    multiPart->append(apisecret);
    multiPart->append(targetImg);
    multiPart->append(faceset);
    QUrl url("https://api-cn.faceplusplus.com/facepp/v3/search");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->post(request,multiPart);
    multiPart->setParent(reply);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();  //loop循环
    if (timer.isActive()){
        //此时 QNetworkReply::finished，响应完成，还尚未超时
        timer.stop();
        if (reply->error() != QNetworkReply::NoError) {
            this->isError=true;
            qDebug() << "In searchFace the error is "<<reply->error()<<reply->errorString();
            return ;
        }else {
            this->isError= false;
//            finishedSearch(reply);
        }
    }else { //超过8秒
        disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        reply->abort();
        reply->deleteLater();
        qDebug() << "联网超时";
    }
}

void Face::storedInDbOp(const QString &filePath)
{

}

void Face::finishedQ(QNetworkReply *reply)
{
    int error = reply->error();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"httpCodes"<<statusCode;
    if(error==QNetworkReply::NoError && statusCode==200){
        QByteArray responseData = reply->readAll();
        QList<QString>faceTokens;
        faceTokens = getfaceToken(responseData);
        qDebug()<<"dajdadjadada"<<responseData<<"  "<<faceTokens;
        if(faceTokens.size()>0){
            addFaceTokens(faceTokens);
        }
        QMap<QString,QVariant>map;
        QJsonDocument documment ;
        map = documment.fromJson(responseData).toVariant().toMap();
        qDebug()<<"responese data:"<<responseData;
        float confidence = map.value("confidence").toFloat();
        qDebug()<<"the confidence is "<<confidence;
    }else{
        qDebug()<<"In finishedQ the error is "<<error<<reply->errorString();
    }
}

void Face::finishedDetect(QNetworkReply *reply)
{
    if(!isError){
        QByteArray responseData = reply->readAll();
        qDebug()<<"responseData"<<responseData;
        QList<QString>faceTokens;
        faceTokens = getfaceToken(responseData);
        if(faceTokens.size()>0){
            for(int i = 0;i<faceTokens.size();i++){
                qDebug()<<"in finishedDetect :"<<faceTokens[i];
                searchFace(faceTokens[i]);
                if(this->confidence>=80.000){
                    qDebug()<<"faceSet已有此人，不将此人脸入库";
                }else{

                    qDebug()<<"加入数据库，关联相关信息";
                }
            }
            addFaceTokens(faceTokens);
        }
    }

}

void Face::finishedSearch(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"httpCodes"<<statusCode;
    qDebug()<<"In finishedSearch :"<<reply->readAll();
    if(reply->error()==QNetworkReply::NoError && statusCode==200){
        QByteArray responseData = reply->readAll();
        QMap<QString,QVariant>map;
        QJsonDocument documment ;
        map = documment.fromJson(responseData).toVariant().toMap();
        double confidence = 0.0;
        QString face_token;
        QJsonArray results = map.value("results").toJsonArray();
        if(!results.isEmpty()){
            QJsonObject obj = results[0].toObject();
            confidence = obj.value("confidence").toDouble();
            face_token = obj.value("face_token").toString();
            qDebug()<<map.value("thresholds").toJsonArray()<<"\n"<<map.value("results").toJsonArray();
    }
        setMaxConfidence(face_token,confidence);
        qDebug()<<map.value("thresholds").toJsonArray()<<"\n"<<map.value("results").toJsonArray();
    }else{
        qDebug()<<"faceSearch error is "<<reply->errorString();
    }


}

void Face::finishFaceTagsInput(QList<QString> tags)
{
    for (auto tmp : tags) {
        qDebug()<<tmp;
    }
}

//
void Face::OpenCVgetFaceRectangle(QString filePath){
    std::string  filepath =filePath.toStdString();
    Mat image=imread(filepath);
    qDebug()<<image.size;
    
    qDebug()<<"image data "<<image.data;
    if(!image.data){
        qDebug() <<("openCV did not find the photo");
        return;
    }
    qDebug() <<("find the photo,start openCV ");
    detectAndDisplay(filePath,image);
}

void Face::detectAndDisplay(QString filePath, Mat frame){

    if (!face_cascade.load(".\\opencv\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml"))
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
    qDebug() << "face size:" << faces.size();
    if (faces.size() <= 0) {
        return;
    }
    QList<Mat> faceROIs;
    for (int i = 0; i <faces.size();i++)
    {
        qDebug()<<faces[i].x<<faces[i].y<<faces[i].width<<faces[i].height;
        Rect roi ;
        roi.x = faces[static_cast<int>(i)].x+2;
        roi.y = faces[static_cast<int>(i)].y+2;
        roi.width=faces[static_cast<int>(i)].width-2;
        roi.height = faces[static_cast<int>(i)].height-2;
        Mat faceROI = frame(roi);
        rectangle(frame,faces[static_cast<int>(i)],Scalar(255,255,255),1,8,0);
        resize(faceROI,faceROI,Size(150,150));
        //            QString filename = "D:/github/photoManagement/faceSet/"+QString::number(i)+".jpg";
        QString photoname = "..\\faceSet\\"+QString::number((i+3)/*+db.getAvatarId()*/)+".jpg";
        qDebug()<<"filename"<<photoname<<"  faceID"<<FaceID;
        faceROIs.push_back(faceROI);
        imwrite(photoname.toStdString(),faceROI);
//        detectFace(photoname);
    }
//    imshow("OpenCv Face Detection",frame);
    FaceTagDialog * ftd = new FaceTagDialog();
    connect(ftd, &FaceTagDialog::finishInput, this, &Face::finishFaceTagsInput);
    ftd->loadFaces(faceROIs);
    ftd->show();

    waitKey(0);

}
bool Face::getIsError() const
{
    return isError;
}

void Face::setIsError(bool value)
{
    this->isError = value;
}

//本来是截ROI的  这里只是toGray 并直方图均衡化了
IplImage* Face::detect( Mat& img, CascadeClassifier& cascade){
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY );
    equalizeHist( gray, gray );
    IplImage pBinary = IplImage(gray);;
    IplImage *input = cvCloneImage(&pBinary);
    return input;
    //cvResize(img, dst);

}

void Face::CompareHist(IplImage *faceImage1, IplImage *faceImage2){
    int HistogramBins = 256;
    float HistogramRange1[2]={0,255};
    float *HistogramRange[1]={&HistogramRange1[0]}; //若是三通道，放三个指针  可以考虑HSV 更科学
    CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    cvCalcHist(&faceImage1, Histogram1);  // IplImage** image,
    cvCalcHist(&faceImage2, Histogram2);
    cvNormalizeHist(Histogram1, 1);  //两幅图片大小不同也没关系 bin都是概率
    cvNormalizeHist(Histogram2, 1);
    // CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似 0最好
    printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));
    printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1,
                                                Histogram2, CV_COMP_BHATTACHARYYA));
    cvReleaseHist(&Histogram1);
    cvReleaseHist(&Histogram2);

}

//最简单的版本，两个Img图片都各只包含一个脸，但这两个脸很可能不同……
void Face::OpenCvfaceCompareConfidence(){
      // face_cascade;
    Mat srcImg =imread("..\\faceSet\\3.jpg");  //1 :3通道读取
    Mat targetImg=imread("..\\faceSet\\5.jpg");
    qDebug() << "can read the OpenCvfaceCompareConfidence 2 images";
    if (!targetImg.data || !srcImg.data){
        qDebug() << "Couldn't read the image";
        return ;
    }
    else {
            IplImage* faceImage1=detect(srcImg,face_cascade);  //Mat->IplImag*
            IplImage* faceImage2=detect(targetImg,face_cascade);
            CompareHist(faceImage1, faceImage2);  //IplImag*才能传入
            //       imshow("image1", Mat(faceImage1));
            //       imshow("image2", Mat(faceImage2));

            //阈值还没确定
            cvReleaseImage(&faceImage1);
            cvReleaseImage(&faceImage2);

    }
}


void Face::CompareFaceHSV(){  //原本的的OpenCvfaceCompareConfidence()用的灰色直方图  HSV肯定准一些
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;    // 装载三张背景环境不同的图像

    src_base = imread( "..\\faceSet\\3.jpg", 1 );
    src_test1 = imread( "..\\faceSet\\5.jpg", 1 );
    src_test2 = imread( "..\\faceSet\\4.jpg", 1 );    // 转换到 HSV
    cvtColor( src_base, hsv_base, CV_BGR2HSV );
    cvtColor( src_test1, hsv_test1, CV_BGR2HSV );
    cvtColor( src_test2, hsv_test2, CV_BGR2HSV );
    hsv_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );
    // 对hue通道使用30个bin,对saturatoin通道使用32个bin
    int h_bins = 50; int s_bins = 60;   int histSize[] = { h_bins, s_bins };
    // hue的取值范围从0到256, saturation取值范围从0到180  不使用亮度，亮度影响较大
    float h_ranges[] = { 0, 256 };
    float s_ranges[] = { 0, 180 };
    const float* ranges[] = { h_ranges, s_ranges };    // 使用第0和第1通道
    int channels[] = { 0, 1 };    // 用到0 1 通道
    Mat hist_base;
    Mat hist_half_down;
    Mat hist_test1;
    Mat hist_test2;    // 计算HSV图像的直方图 1代表输入图像个数
    calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
    calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
    normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
    calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
    normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );
    calcHist( &hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false );
    normalize( hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat() );    //应用不同的直方图对比方法
    // HISTCMP_CORREL 1  HISTCMP_CHISQR 0  HISTCMP_INTERSECT  HISTCMP_BHATTACHARYYA 0
    for( int i = 0; i < 4; i++ )      {
        int compare_method = i;
        double base_base = compareHist( hist_base, hist_base, compare_method );
        double base_half = compareHist( hist_base, hist_half_down, compare_method );
        double base_test1 = compareHist( hist_base, hist_test1, compare_method );
        double base_test2 = compareHist( hist_base, hist_test2, compare_method );
        printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half , base_test1, base_test2 );
    }
        printf( "Done \n" );
        //我个人建议 只使用HISTCMP_CORREL >0.5且HISTCMP_BHATTACHARYYA<0.5  不过我觉得只能判断是不是人 不能判断是不是同一个人  没法用openCv提取的特征点来假设 要不换方向
}

void Face::getPilesFaces(){  //先弄出来5个脸
    string filepath1=".\\zwphotos\\test3.jpg";
//    QString filePath1=".\\zwphotos\\test3.jpg";
//    std::string  filepath1 =filePath1.toStdString();
//    QString filePath=".\\zwphotos\\testbig.jpg";
//    std::string  filepath =filePath.toStdString();
    string filepath=".\\zwphotos\\test7.jpg";
    Mat image=imread(filepath);
    Mat image1=imread(filepath1);
 while(image.cols>=1200){
     resize(image,image,Size(image.cols*0.8,image.rows*0.8));
     }
    if(!image.data){
        qDebug() <<("openCV did not find the photo");
        return;
    }
    qDebug() <<("find the photo,start openCV ");
    if (!face_cascade.load(".\\opencv\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml"))
    {
        qDebug() <<("--(!)Error loading face cascade\n");
        return ;
    }
    std::vector<Rect> faces;
    int scale=1;
    Mat frame_gray;
    cvtColor(image, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray ); //直方图均衡化
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, 0 );
    qDebug() <<faces.size();
    if(faces.size()==0){
        qDebug()<<" no face!";
        return;
    }
    for (int i = 0; i <faces.size();i++)
    {
        qDebug()<<faces[i].x<<faces[i].y<<faces[i].width<<faces[i].height;
        Rect roi ;
        roi.x = faces[static_cast<int>(i)].x+2;
        roi.y = faces[static_cast<int>(i)].y+2;
        roi.width=faces[static_cast<int>(i)].width-2;
        roi.height = faces[static_cast<int>(i)].height-2;
        Mat faceROI = image(roi);
        rectangle(image,faces[static_cast<int   >(i)],Scalar(255,255,255),1,8,0);
        resize(faceROI,faceROI,Size(150,150));
        //            QString filename = "D:/github/photoManagement/faceSet/"+QString::number(i)+".jpg";
        QString photoname = "..\\faceSet\\"+QString::number((i+51)/*+db.getAvatarId()*/)+".jpg";
        qDebug()<<"filename"<<photoname<<"  faceID"<<FaceID;
        imwrite(photoname.toStdString(),faceROI);
    }


    waitKey(0);
}
