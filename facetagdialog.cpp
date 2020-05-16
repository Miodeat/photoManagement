#include "facetagdialog.h"
#include "ui_facetagdialog.h"
#include <QPushButton>

FaceTagDialog::FaceTagDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceTagDialog)
{
    ui->setupUi(this);
    faceIndex = -1;
}

FaceTagDialog::~FaceTagDialog()
{
    delete ui;
}

void FaceTagDialog::loadFace(cv::Mat face)
{
    QPixmap facePix = cvMatToQPixmap(face);
    this->faces.push_back(facePix); // add face icon to faces
}

void FaceTagDialog::loadFaces(QList<cv::Mat> faces)
{
    if (faces.isEmpty()){
        return;
    }

    faceIndex = 0; // set faceIndex

    for (cv::Mat face : faces) {
        this->faces.push_back(cvMatToQPixmap(face)); // add face icons to faces
    }
    ui->faceIconLabel->setPixmap(this->faces.at(faceIndex));

    if (faces.size() > 1) {
        // change the text of Ok button to Next
        QPushButton * btn = ui->buttonBox->button(QDialogButtonBox::Ok);
        btn->setText("Next");
    }
}

QImage FaceTagDialog::cvMatToQimage(const cv::Mat &src)
{
    switch (src.type()) {
    // 8 bits, 4 channels
    case CV_8UC4: {
        QImage img(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_ARGB32);
        return img;
    }
    // 8 bits, 3 channels
    case CV_8UC3: {
        QImage img(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    // 8 bits, 1 channels
    case CV_8UC1: {
        QImage img(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_Grayscale8);
        return img;
    }
    // others
    default: {
        qDebug() << "illegal Mat type: " << src.type();
        return QImage();
    }
    }
}

QPixmap FaceTagDialog::cvMatToQPixmap(const cv::Mat &src)
{
    return QPixmap::fromImage(cvMatToQimage(src));
}

QList<QString> FaceTagDialog::getTags()
{
    return this->tags;
}

void FaceTagDialog::on_buttonBox_accepted()
{
    // Insurance
    if (faces.isEmpty()) {
        return;
    }

    this->tags.push_back(ui->faceTagLineEdit->text());
    faceIndex++;
    if (faceIndex == faces.length() - 1) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ok"); // change the text of Ok button to Ok
        ui->faceIconLabel->setPixmap(faces.at(faceIndex)); // load next picture
        this->show();
    }
    else if (faceIndex < faces.length() - 1) {
        ui->faceIconLabel->setPixmap(faces.at(faceIndex)); // load next picture
        this->show();
    }
    else {
        emit finishInput(this->tags);
    }

}

void FaceTagDialog::resizeEvent(QResizeEvent *event)
{
    if (faceIndex == -1){
        return;
    }
    QPixmap scaledFace = faces.at(faceIndex).scaled(ui->faceScrollArea->size(), Qt::KeepAspectRatio);
    ui->faceIconLabel->setPixmap(scaledFace);
}
