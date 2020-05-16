#ifndef SEARCHRESULTDIALOG_H
#define SEARCHRESULTDIALOG_H

#include <QDialog>

namespace Ui {
class SearchResultDialog;
}

class SearchResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchResultDialog(QWidget *parent = nullptr);
    ~SearchResultDialog();

    // show the results of searching in photoWall
    //
    // @param paths: a QStringList that stores all paths of result
    // @return: void
    void showSearchResult(QStringList paths);

private:
    Ui::SearchResultDialog *ui;

    QStringList resultPaths; // store all file paths of result photo

    // add new thumbnail to the photoWall, method "ui->photoWall->show()"
    // should be invoked after invoking this method.
    //
    // @param photoName: file path of photo, stored as QString
    // @return: void
    void addNewIcon(QString photoName);

private slots:
    // show the origin picture after the click on item of photoWall
    //
    // @param
    // @return
    void photoClicked();
};

#endif // SEARCHRESULTDIALOG_H
