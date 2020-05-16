#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "antigeocode.h"
#include "exif.h"
#include "dbpostgis.h"
#include <QFileDialog>
#include "face.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/opencv.hpp>
#include "photodialog.h"
#include <QListWidgetItem>
#include "facetagdialog.h"
#include "dbpostgresql.h"
#include "searchpannel.h"
#include "visualize.h"


using namespace  cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    //used to begin photo recoginzation
    void beginDetect();
    //used to clear some params
    void clear();
public:
    QList<QString> getFilePath() const;
    void setFilePath(const QList<QString> &filePath);
    void showPhotoWallList(QString photoName);
    QString getPhotoName(QString photoPath);
    void getThumbNailPhotos();
    void toNewWidget();
    
private slots:
    void openFile();
    void finishedClick();

    // open search pannel when actionSearch is triggered
    //
    // @param
    // @return
    void on_actionSearch_triggered();

    void on_actionVisualize_triggered();

signals:
    void sendPhotoData(QListWidgetItem);
private:

    Ui::MainWindow *ui;
    dbPostgis db;
    Face face;
    //used to store the path when open new photos and pass them to other class
    QList<QString> filePath;
    //data/photo目录下的所有原图名称，目的是不重复保存图片。
    QList<QString> OphotoNames;
    easyexif::EXIFInfo* exif;
};

#endif // MAINWINDOW_H
