/********************************************************************************
** Form generated from reading UI file 'facetagdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACETAGDIALOG_H
#define UI_FACETAGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceTagDialog
{
public:
    QGridLayout *gridLayout;
    QScrollArea *faceScrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *gridLayoutWidget;
    QGridLayout *faceLayout;
    QLabel *faceIconLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *tipLabel;
    QLineEdit *faceTagLineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FaceTagDialog)
    {
        if (FaceTagDialog->objectName().isEmpty())
            FaceTagDialog->setObjectName(QString::fromUtf8("FaceTagDialog"));
        FaceTagDialog->resize(475, 362);
        gridLayout = new QGridLayout(FaceTagDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        faceScrollArea = new QScrollArea(FaceTagDialog);
        faceScrollArea->setObjectName(QString::fromUtf8("faceScrollArea"));
        faceScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 451, 275));
        gridLayoutWidget = new QWidget(scrollAreaWidgetContents);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, -1, 511, 311));
        faceLayout = new QGridLayout(gridLayoutWidget);
        faceLayout->setObjectName(QString::fromUtf8("faceLayout"));
        faceLayout->setContentsMargins(0, 0, 0, 0);
        faceIconLabel = new QLabel(gridLayoutWidget);
        faceIconLabel->setObjectName(QString::fromUtf8("faceIconLabel"));

        faceLayout->addWidget(faceIconLabel, 0, 0, 1, 1);

        faceScrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(faceScrollArea, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tipLabel = new QLabel(FaceTagDialog);
        tipLabel->setObjectName(QString::fromUtf8("tipLabel"));

        horizontalLayout_2->addWidget(tipLabel);

        faceTagLineEdit = new QLineEdit(FaceTagDialog);
        faceTagLineEdit->setObjectName(QString::fromUtf8("faceTagLineEdit"));

        horizontalLayout_2->addWidget(faceTagLineEdit);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(FaceTagDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(FaceTagDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FaceTagDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FaceTagDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FaceTagDialog);
    } // setupUi

    void retranslateUi(QDialog *FaceTagDialog)
    {
        FaceTagDialog->setWindowTitle(QApplication::translate("FaceTagDialog", "Dialog", nullptr));
        faceIconLabel->setText(QString());
        tipLabel->setText(QApplication::translate("FaceTagDialog", "\350\257\267\350\276\223\345\205\245\344\273\226\347\232\204\345\220\215\345\255\227:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FaceTagDialog: public Ui_FaceTagDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACETAGDIALOG_H
