/********************************************************************************
** Form generated from reading UI file 'searchpannel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHPANNEL_H
#define UI_SEARCHPANNEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SearchPannel
{
public:
    QLabel *timeLabel;
    QDateTimeEdit *dateTimeEdit;
    QLabel *locationLabel;
    QLineEdit *provinceLineEdit;
    QLabel *provinceLabel;
    QLineEdit *cityLineEdit;
    QLabel *cityLabel;
    QLabel *blockLabel;
    QLineEdit *blockLineEdit;
    QLabel *detailLocLabel;
    QLineEdit *detailLocLineEdit;
    QLabel *facesLabel;
    QLineEdit *facesLineEdit;
    QLabel *labelLabel;
    QLineEdit *lableLineEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *SearchPannel)
    {
        if (SearchPannel->objectName().isEmpty())
            SearchPannel->setObjectName(QString::fromUtf8("SearchPannel"));
        SearchPannel->resize(608, 385);
        timeLabel = new QLabel(SearchPannel);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setGeometry(QRect(30, 40, 61, 41));
        dateTimeEdit = new QDateTimeEdit(SearchPannel);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(100, 50, 194, 22));
        QFont font;
        font.setPointSize(12);
        dateTimeEdit->setFont(font);
        locationLabel = new QLabel(SearchPannel);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));
        locationLabel->setGeometry(QRect(30, 100, 61, 31));
        QFont font1;
        font1.setPointSize(14);
        locationLabel->setFont(font1);
        provinceLineEdit = new QLineEdit(SearchPannel);
        provinceLineEdit->setObjectName(QString::fromUtf8("provinceLineEdit"));
        provinceLineEdit->setGeometry(QRect(100, 100, 113, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        provinceLineEdit->setFont(font2);
        provinceLabel = new QLabel(SearchPannel);
        provinceLabel->setObjectName(QString::fromUtf8("provinceLabel"));
        provinceLabel->setGeometry(QRect(220, 100, 31, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(14);
        provinceLabel->setFont(font3);
        cityLineEdit = new QLineEdit(SearchPannel);
        cityLineEdit->setObjectName(QString::fromUtf8("cityLineEdit"));
        cityLineEdit->setGeometry(QRect(250, 100, 113, 31));
        cityLineEdit->setFont(font2);
        cityLabel = new QLabel(SearchPannel);
        cityLabel->setObjectName(QString::fromUtf8("cityLabel"));
        cityLabel->setGeometry(QRect(370, 100, 31, 31));
        cityLabel->setFont(font3);
        blockLabel = new QLabel(SearchPannel);
        blockLabel->setObjectName(QString::fromUtf8("blockLabel"));
        blockLabel->setGeometry(QRect(520, 100, 61, 31));
        blockLabel->setFont(font3);
        blockLineEdit = new QLineEdit(SearchPannel);
        blockLineEdit->setObjectName(QString::fromUtf8("blockLineEdit"));
        blockLineEdit->setGeometry(QRect(400, 100, 113, 31));
        blockLineEdit->setFont(font2);
        detailLocLabel = new QLabel(SearchPannel);
        detailLocLabel->setObjectName(QString::fromUtf8("detailLocLabel"));
        detailLocLabel->setGeometry(QRect(100, 150, 111, 31));
        detailLocLabel->setFont(font3);
        detailLocLineEdit = new QLineEdit(SearchPannel);
        detailLocLineEdit->setObjectName(QString::fromUtf8("detailLocLineEdit"));
        detailLocLineEdit->setGeometry(QRect(220, 150, 311, 31));
        detailLocLineEdit->setFont(font2);
        facesLabel = new QLabel(SearchPannel);
        facesLabel->setObjectName(QString::fromUtf8("facesLabel"));
        facesLabel->setGeometry(QRect(30, 210, 201, 31));
        facesLabel->setFont(font1);
        facesLineEdit = new QLineEdit(SearchPannel);
        facesLineEdit->setObjectName(QString::fromUtf8("facesLineEdit"));
        facesLineEdit->setGeometry(QRect(240, 210, 331, 31));
        facesLineEdit->setFont(font);
        labelLabel = new QLabel(SearchPannel);
        labelLabel->setObjectName(QString::fromUtf8("labelLabel"));
        labelLabel->setGeometry(QRect(30, 260, 201, 31));
        labelLabel->setFont(font1);
        lableLineEdit = new QLineEdit(SearchPannel);
        lableLineEdit->setObjectName(QString::fromUtf8("lableLineEdit"));
        lableLineEdit->setGeometry(QRect(240, 260, 331, 31));
        lableLineEdit->setFont(font);
        okBtn = new QPushButton(SearchPannel);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(340, 330, 111, 41));
        okBtn->setFont(font);
        cancelBtn = new QPushButton(SearchPannel);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(470, 330, 111, 41));
        cancelBtn->setFont(font);

        retranslateUi(SearchPannel);

        QMetaObject::connectSlotsByName(SearchPannel);
    } // setupUi

    void retranslateUi(QDialog *SearchPannel)
    {
        SearchPannel->setWindowTitle(QApplication::translate("SearchPannel", "\346\220\234\347\264\242\351\235\242\346\235\277", nullptr));
        timeLabel->setText(QApplication::translate("SearchPannel", "<html><head/><body><p><span style=\" font-size:14pt;\">\346\227\266\351\227\264:</span></p></body></html>", nullptr));
        locationLabel->setText(QApplication::translate("SearchPannel", "\345\234\260\347\202\271:", nullptr));
        provinceLabel->setText(QApplication::translate("SearchPannel", "\347\234\201", nullptr));
        cityLabel->setText(QApplication::translate("SearchPannel", "\345\270\202", nullptr));
        blockLabel->setText(QApplication::translate("SearchPannel", "\345\214\272/\345\216\277", nullptr));
        detailLocLabel->setText(QApplication::translate("SearchPannel", "\350\257\246\347\273\206\345\234\260\345\235\200\357\274\232", nullptr));
        facesLabel->setText(QApplication::translate("SearchPannel", "\344\272\272\350\204\270(\344\273\245\342\200\234/\342\200\235\345\210\206\351\232\224\357\274\211", nullptr));
        labelLabel->setText(QApplication::translate("SearchPannel", "\346\240\207\347\255\276(\344\273\245\342\200\234/\342\200\235\345\210\206\351\232\224\357\274\211", nullptr));
        okBtn->setText(QApplication::translate("SearchPannel", "\347\241\256\350\256\244", nullptr));
        cancelBtn->setText(QApplication::translate("SearchPannel", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchPannel: public Ui_SearchPannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHPANNEL_H
