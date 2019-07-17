#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "antigeocode.h"
#include "exif.h"
#include "dbpostgis.h"

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


private:
    Ui::MainWindow *ui;
    easyexif::EXIFInfo exif;
    dbPostgis db;

};

#endif // MAINWINDOW_H
