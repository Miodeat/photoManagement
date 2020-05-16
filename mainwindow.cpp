#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //face.OpenCvfaceCompareConfidence();
//    face.OpenCVgetFaceRectangle(".\\test1.jpg");
    //face.getPilesFaces();
    face.CompareFaceHSV();
    ui->setupUi(this);
    filePath={};
    getThumbNailPhotos();
    connect(ui->photoWall,&QListWidget::itemClicked,this,&MainWindow::finishedClick);
    qDebug()<<"test whether is clicked";
    //    exif.loadFile(QString("../../photoManagement2/test1.jpg"));
    //    db.getExif(exif);
        db.connect();

    //    db.insertAvatarInfo("向日葵");
    //    db.insertPhotoInfo("小雏菊");
    //    db.queryPhoto();
    //    db.queryAvatar();

    //     face.connetNetWork();
    //     face.test();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::beginDetect()
{
    if(!filePath.isEmpty()){
        for(auto tmp:filePath){
            qDebug()<<"tmp"<<tmp;
            face.OpenCVgetFaceRectangle(tmp);
        }
    }
}
//打开文件
void MainWindow::clear()
{
    filePath = {};
}

void MainWindow::openFile()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("选择图片");
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    for(auto tmp:fileNames){
        qDebug()<<tmp;
        if(tmp!=""){
            //            face.OpenCVgetFaceRectangle(tmp);
        }
        easyexif::EXIFInfo exif;
        exif.loadFile(tmp);
        QString photoName = "./data/photos/"+getPhotoName(tmp);
        qDebug()<<photoName;

        qDebug()<<"formatted"<<exif.formattedAdd;
        Mat image = imread(tmp.toLocal8Bit().toStdString().c_str());
        qDebug()<<image.data;
        //保存原图片，已经保证中文不乱码
        DBPostGreSQL *db = new DBPostGreSQL(&exif);
        db->setPhotoPath(photoName);
        db->startRuKu();
        imwrite(photoName.toLocal8Bit().toStdString().c_str(),image);
        QString photoNameNail ="./data/thumbnails/"+getPhotoName(tmp);
        cv::resize(image,image,Size(100,100));
        //保存缩略图，照片墙上显示的是缩略图，大小如上
        imwrite(photoNameNail.toLocal8Bit().toStdString().c_str(),image);
        //不重复显示图片
        bool flag = true;
        if(this->filePath.size()>0){
            for(int i = 0;i<filePath.size();i++){
                //compare结果为-1 0 1 分别对应小于等于大于
                if(!filePath[i].compare(photoNameNail)){
                    flag = false;                }
            }
        }
        if(flag){
            this->filePath.push_back(photoNameNail);
            qDebug()<<filePath.size();
            showPhotoWallList(photoNameNail);
        }

        Face * faceDetect = new Face();
        faceDetect->detectAndDisplay(tmp, image);
    }


    //    beginDetect();
    //    clear();

}

void MainWindow::finishedClick()
{

    int id = ui->photoWall->currentRow();
    qDebug()<<ui->photoWall->currentItem();
    QListWidgetItem *item =ui->photoWall->currentItem();
    qDebug()<<ui->photoWall->currentItem()->icon();
    photoDialog *p = new photoDialog();
    p->showPhotoAndInfo(filePath.at(id));
    p->show();



    //qDebug()<<item->icon();
    qDebug()<<"test whether is clicked";
}

QList<QString> MainWindow::getFilePath() const
{
    return filePath;
}

void MainWindow::setFilePath(const QList<QString> &filePath)
{
    this->filePath = filePath;
}

void MainWindow::showPhotoWallList(QString photoName)
{
    //    ui->photoWall->resize(365,400);
    ui->photoWall->setViewMode(QListView::IconMode);
    ui->photoWall->setIconSize(QSize(100,100));
    ui->photoWall->setSpacing(10);
    ui->photoWall->setResizeMode(QListView::Adjust);
    ui->photoWall->setMovement(QListView::Static);
    QListWidgetItem *imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(photoName));
    imageItem->setSizeHint(QSize(110,110));
    //imageItem->setText(photoName);
    ui->photoWall->addItem(imageItem);

    ui->photoWall->show();
}

QString MainWindow::getPhotoName(QString photoPath)
{
    QStringList tempList = photoPath.split("/");
    QString photoName;
    if(tempList.size()>0){
        photoName = tempList[tempList.size()-1];
    }
    return photoName;
}

void MainWindow::getThumbNailPhotos()
{
    //later I will write a funtion to get currentPath.
    QDir dir("./data/thumbnails");
    QStringList nameFilters;
    nameFilters<<"*.jpg"<<"*.jpeg"<<"*.png";
    dir.setFilter(QDir::Files|QDir::Readable);
    dir.setSorting(QDir::Size|QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    if(list.size()>0){
        for(int i = 0;i<list.size();i++){
            QFileInfo  fileInfo = list.at(i);
            //get thumbNails' full path
            QString name = fileInfo.path()+"/"+fileInfo.fileName();
            this->filePath.push_back(name);
            showPhotoWallList(name);
        }
    }
}

void MainWindow::toNewWidget()
{

}

void MainWindow::on_actionSearch_triggered()
{
    SearchPannel * searchPan = new SearchPannel();
    searchPan->show();
}

void MainWindow::on_actionVisualize_triggered()
{
    Visualize *visualization = new Visualize();
    visualization->show();
}
