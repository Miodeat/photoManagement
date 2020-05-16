#ifndef PHOTODIALOG_H
#define PHOTODIALOG_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class photoDialog;
}

class photoDialog : public QWidget
{
    Q_OBJECT
public:
    explicit photoDialog(QWidget *parent = nullptr);

    ~photoDialog() override;

private:
    Ui::photoDialog *ui;
    QPixmap* imgPtr;

    // show when and where the photo was taken
    //
    // @param filePath: the path of image
    // @return
    void setPhotoTimeAndLoc(QString filePath);

    // adjust size of image by using override resizeEvent, which will be triggered when the size of dialog changed
    //
    // @param event: the pointer of QResizeEvent, will be given by program itself
    // @return
    virtual void resizeEvent(QResizeEvent* event) override;

public:
    // by invoking this function, the chosen image will be paint in the dialog
    //
    // @param filepath: the path of image
    // @return:
    void showPhotoAndInfo(QString filePath);

signals:
    // a signal with labels of the photo
    void sendPhotoLabel(QString labels);

private slots:
    // this slot will be invoked to add labels of the photo
    void on_addConfirm_btn_clicked();
};

#endif // PHOTODIALOG_H
