/********************************************************************************
** Form generated from reading UI file 'photodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHOTODIALOG_H
#define UI_PHOTODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_photoDialog
{
public:
    QHBoxLayout *dialog_layout;
    QScrollArea *imgLable_scroll;
    QWidget *imgLabel_layout;
    QGridLayout *gridLayout;
    QLabel *imgLabel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *addLabelArea_layout;
    QPushButton *addConfirm_btn;
    QLabel *textLabel;
    QScrollArea *labelInput_scroll;
    QWidget *labelInput_layout;
    QGridLayout *gridLayout_2;
    QTextEdit *labelInput_txtEdit;
    QSpacerItem *verticalSpacer_middle;
    QLabel *label_time;
    QLabel *label_location;
    QSpacerItem *verticalSpacer_bottom;

    void setupUi(QWidget *photoDialog)
    {
        if (photoDialog->objectName().isEmpty())
            photoDialog->setObjectName(QString::fromUtf8("photoDialog"));
        photoDialog->resize(1132, 503);
        dialog_layout = new QHBoxLayout(photoDialog);
        dialog_layout->setObjectName(QString::fromUtf8("dialog_layout"));
        imgLable_scroll = new QScrollArea(photoDialog);
        imgLable_scroll->setObjectName(QString::fromUtf8("imgLable_scroll"));
        imgLable_scroll->setWidgetResizable(true);
        imgLabel_layout = new QWidget();
        imgLabel_layout->setObjectName(QString::fromUtf8("imgLabel_layout"));
        imgLabel_layout->setGeometry(QRect(0, 0, 550, 479));
        gridLayout = new QGridLayout(imgLabel_layout);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        imgLabel = new QLabel(imgLabel_layout);
        imgLabel->setObjectName(QString::fromUtf8("imgLabel"));

        gridLayout->addWidget(imgLabel, 0, 0, 1, 1);

        imgLable_scroll->setWidget(imgLabel_layout);

        dialog_layout->addWidget(imgLable_scroll);

        groupBox = new QGroupBox(photoDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addLabelArea_layout = new QGridLayout();
        addLabelArea_layout->setObjectName(QString::fromUtf8("addLabelArea_layout"));
        addConfirm_btn = new QPushButton(groupBox);
        addConfirm_btn->setObjectName(QString::fromUtf8("addConfirm_btn"));

        addLabelArea_layout->addWidget(addConfirm_btn, 1, 1, 1, 1);

        textLabel = new QLabel(groupBox);
        textLabel->setObjectName(QString::fromUtf8("textLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        textLabel->setFont(font);

        addLabelArea_layout->addWidget(textLabel, 0, 0, 1, 1);

        labelInput_scroll = new QScrollArea(groupBox);
        labelInput_scroll->setObjectName(QString::fromUtf8("labelInput_scroll"));
        labelInput_scroll->setWidgetResizable(true);
        labelInput_layout = new QWidget();
        labelInput_layout->setObjectName(QString::fromUtf8("labelInput_layout"));
        labelInput_layout->setGeometry(QRect(0, 0, 407, 214));
        gridLayout_2 = new QGridLayout(labelInput_layout);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelInput_txtEdit = new QTextEdit(labelInput_layout);
        labelInput_txtEdit->setObjectName(QString::fromUtf8("labelInput_txtEdit"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        labelInput_txtEdit->setFont(font1);

        gridLayout_2->addWidget(labelInput_txtEdit, 0, 0, 1, 1);

        labelInput_scroll->setWidget(labelInput_layout);

        addLabelArea_layout->addWidget(labelInput_scroll, 0, 1, 1, 1);


        verticalLayout->addLayout(addLabelArea_layout);

        verticalSpacer_middle = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_middle);

        label_time = new QLabel(groupBox);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        verticalLayout->addWidget(label_time);

        label_location = new QLabel(groupBox);
        label_location->setObjectName(QString::fromUtf8("label_location"));

        verticalLayout->addWidget(label_location);

        verticalSpacer_bottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_bottom);


        dialog_layout->addWidget(groupBox);


        retranslateUi(photoDialog);

        QMetaObject::connectSlotsByName(photoDialog);
    } // setupUi

    void retranslateUi(QWidget *photoDialog)
    {
        photoDialog->setWindowTitle(QApplication::translate("photoDialog", "Form", nullptr));
        imgLabel->setText(QString());
        groupBox->setTitle(QString());
        addConfirm_btn->setText(QApplication::translate("photoDialog", "\347\241\256\350\256\244\346\267\273\345\212\240", nullptr));
        textLabel->setText(QApplication::translate("photoDialog", "\346\267\273\345\212\240\345\233\276\347\211\207\346\240\207\347\255\276\357\274\232", nullptr));
        label_time->setText(QApplication::translate("photoDialog", "\346\213\215\346\221\204\346\227\266\351\227\264\357\274\232", nullptr));
        label_location->setText(QApplication::translate("photoDialog", "\346\213\215\346\221\204\345\234\260\347\202\271\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class photoDialog: public Ui_photoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHOTODIALOG_H
