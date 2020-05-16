/********************************************************************************
** Form generated from reading UI file 'searchresultdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHRESULTDIALOG_H
#define UI_SEARCHRESULTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchResultDialog
{
public:
    QListWidget *photoWall;

    void setupUi(QDialog *SearchResultDialog)
    {
        if (SearchResultDialog->objectName().isEmpty())
            SearchResultDialog->setObjectName(QString::fromUtf8("SearchResultDialog"));
        SearchResultDialog->resize(620, 366);
        photoWall = new QListWidget(SearchResultDialog);
        photoWall->setObjectName(QString::fromUtf8("photoWall"));
        photoWall->setGeometry(QRect(0, 0, 621, 371));

        retranslateUi(SearchResultDialog);

        QMetaObject::connectSlotsByName(SearchResultDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchResultDialog)
    {
        SearchResultDialog->setWindowTitle(QApplication::translate("SearchResultDialog", "\346\220\234\347\264\242\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchResultDialog: public Ui_SearchResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHRESULTDIALOG_H
