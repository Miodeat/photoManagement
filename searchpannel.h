#ifndef SEARCHPANNEL_H
#define SEARCHPANNEL_H

#include <QDialog>
#include "searchresultdialog.h"

namespace Ui {
class SearchPannel;
}

class SearchPannel : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPannel(QWidget *parent = nullptr);
    ~SearchPannel();

private slots:
    // open new dialog to show search results
    //
    // @param
    // @return
    void on_okBtn_clicked();


    // close current dialog
    //
    // @param
    // @return
    void on_cancelBtn_clicked();

private:
    Ui::SearchPannel *ui;
};

#endif // SEARCHPANNEL_H
