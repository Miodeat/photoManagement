#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    exif.loadFile(QString("E:\\DaChuang\\DaChuang\\exifFile.jpg"));

}

MainWindow::~MainWindow()
{
    delete ui;
}