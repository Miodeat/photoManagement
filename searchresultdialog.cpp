#include "searchresultdialog.h"
#include "ui_searchresultdialog.h"
#include "photodialog.h"

SearchResultDialog::SearchResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchResultDialog)
{
    ui->setupUi(this);
}

SearchResultDialog::~SearchResultDialog()
{
    delete ui;
}

void SearchResultDialog::showSearchResult(QStringList paths)
{
    this->resultPaths = paths; // set resultPaths to store file paths

    for (auto path : paths) {
        addNewIcon(path);
    }

    ui->photoWall->show();
}

void SearchResultDialog::addNewIcon(QString photoName)
{
    // set photoWall
    ui->photoWall->setViewMode(QListView::IconMode);
    ui->photoWall->setIconSize(QSize(100,100));
    ui->photoWall->setSpacing(10);
    ui->photoWall->setResizeMode(QListView::Adjust);
    ui->photoWall->setMovement(QListView::Static);
    // get new icon
    QListWidgetItem *imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(photoName));
    imageItem->setSizeHint(QSize(110,110));

    ui->photoWall->addItem(imageItem); // add new item
}

void SearchResultDialog::photoClicked()
{
    int id = ui->photoWall->currentRow();

    photoDialog *p = new photoDialog();
    p->showPhotoAndInfo(resultPaths.at(id));
    p->show();
}
