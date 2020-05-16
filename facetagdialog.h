#ifndef FACETAGDIALOG_H
#define FACETAGDIALOG_H

#include <QDialog>
#include "opencv/cv.h"
#include <QDebug>

namespace Ui {
class FaceTagDialog;
}

class FaceTagDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FaceTagDialog(QWidget *parent = nullptr);
    ~FaceTagDialog() override;

    // load face icon
    //
    // @param face: a picture of face as "Mat"
    // @return:
    void loadFace(cv::Mat face);

    // load multiple face icons
    //
    // @param faces: a QList contains many Mats which are picture of faces
    // @return:
    void loadFaces(QList<cv::Mat> faces);

    // turn Mat into Qimage
    //
    // @param src: a Mat need to be turned
    // @return: a Qimage parse from parameter
    QImage cvMatToQimage(const cv::Mat &src);

    // turn Mat into QPixmap
    //
    // @param src: a Mat need to be turned
    // @return: a QPixmap parse from parameter
    QPixmap cvMatToQPixmap(const cv::Mat &src);

    // get tags of face icons
    //
    // @param
    // @return: a QList contains all tags(as QString) of face icons
    QList<QString> getTags();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FaceTagDialog *ui;
    QList<QString> tags; // store tags of face
    QList<QPixmap> faces; // store face icon
    int faceIndex; // store the position of current face in faces

    // resize face icon when dialog size change
    //
    // @param event: will be given by exec()
    // @return:
    virtual void resizeEvent(QResizeEvent* event) override;

signals:
    // a signal which send tags of faces to relative slot
    //
    // @param tags: a QList store tags of faces
    // @return
    void finishInput(QList<QString> tags);
};

#endif // FACETAGDIALOG_H
