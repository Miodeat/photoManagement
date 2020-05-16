#include "visualize.h"
#include "ui_visualize.h"

#include<QDebug>
#include<QtWebEngineWidgets>

Visualize::Visualize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Visualize)
{
    ui->setupUi(this);
}

Visualize::~Visualize()
{
    delete ui;
}

void Visualize::on_btnCancel_clicked()
{
    this->close();
}

void Visualize::on_btnStart_clicked()
{
    QString path = QDir::currentPath();
    QUrl url(path.append("/Map.html"));
    //   QUrl url("file:///D:/DaChuang/MyTeat/index.html");
    ui->view->load(url);
}
