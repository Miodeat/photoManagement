#include "photodialog.h"
#include "ui_photodialog.h"
#include "mainwindow.h"
#include "dbpostgis.h"
#include <QSize>

photoDialog::photoDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photoDialog)
{
    ui->setupUi(this);
    ui->dialog_layout->setStretchFactor(ui->imgLable_scroll, 3);
    ui->dialog_layout->setStretchFactor(ui->groupBox, 1);
    ui->addLabelArea_layout->setColumnStretch(0, 1);
    ui->addLabelArea_layout->setColumnStretch(1, 2);
    ui->imgLabel->setAlignment(Qt::AlignCenter);
    ui->verticalSpacer_bottom->changeSize(20, 20);
}

photoDialog::~photoDialog()
{
    delete ui;
}

void photoDialog::setPhotoTimeAndLoc(QString filePath)
{
    QList<QString> attList;
    attList.push_back("taken_time");
    attList.push_back("taken_place");
    dbPostgis db;
    // "connect" method should return a flag to tell whether the connection is active or not. However, the class "dbPostgis" is not perfect now.
//    if(db.connect()) {
//        db.connect();
//        QList<QString> result = db.getAttributeByPath(filePath, attList);
//        ui->label_time->setText(QString("拍摄时间：" + result[0]).toUtf8());
//        ui->label_location->setText(QString("拍摄地点：" + result[1]).toUtf8());
    //    }
}

void photoDialog::resizeEvent(QResizeEvent *event)
{
    if(imgPtr != nullptr){
        QPixmap scaledImg = imgPtr->scaled(ui->imgLable_scroll->size(), Qt::KeepAspectRatio);
        ui->imgLabel->setPixmap(scaledImg);
    }
}


void photoDialog::showPhotoAndInfo(QString filePath)
{
    QStringList splited = filePath.split("/");
    // get origin photo path
    QString oriPath = "./data/photos/" + *--splited.end();
    // show image
    QPixmap img(oriPath);
    imgPtr = new QPixmap(img);
//    QPixmap scaledImg = img.scaled(, Qt::KeepAspectRatio);
//    ui->imgLabel->setPixmap(img);
    // set time and location
    setPhotoTimeAndLoc(oriPath);
}

void photoDialog::on_addConfirm_btn_clicked()
{
    QString labels = ui->labelInput_txtEdit->toPlainText();
    qDebug() << labels;
    emit sendPhotoLabel(labels);
}
