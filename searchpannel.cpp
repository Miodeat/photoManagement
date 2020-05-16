#include "searchpannel.h"
#include "ui_searchpannel.h"
#include <QTime>
#include <QString>
#include <QStringList>

SearchPannel::SearchPannel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPannel)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setCalendarPopup(true); // enable to use calendar to choose date
}

SearchPannel::~SearchPannel()
{
    delete ui;
}

void SearchPannel::on_okBtn_clicked()
{
    // get all information from input widgets
    QDateTime time = ui->dateTimeEdit->dateTime();
    QString province = ui->provinceLineEdit->text();
    QString city = ui->cityLineEdit->text();
    QString block = ui->blockLineEdit->text();
    QString detailLoc = ui->detailLocLineEdit->text();
    QString faces = ui->facesLineEdit->text();
    QString labels = ui->lableLineEdit->text();

    // split strings by '/' in order to get multiple tags
    QStringList facesList = faces.split("/");
    QStringList labelsList = labels.split("/");

    // invoke interfaces of database


    // show results in SearchResultDialog
    SearchResultDialog * searchReDia = new SearchResultDialog();
    searchReDia->showSearchResult(QStringList());
    searchReDia->show();

    this->close();
}

void SearchPannel::on_cancelBtn_clicked()
{
    this->close();
}
