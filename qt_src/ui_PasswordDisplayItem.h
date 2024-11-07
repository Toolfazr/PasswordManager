/********************************************************************************
** Form generated from reading UI file 'PasswordDisplayItem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDDISPLAYITEM_H
#define UI_PASSWORDDISPLAYITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasswordDisplayItem
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QTextBrowser *textBrowser;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *changeBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *PasswordDisplayItem)
    {
        if (PasswordDisplayItem->objectName().isEmpty())
            PasswordDisplayItem->setObjectName(QString::fromUtf8("PasswordDisplayItem"));
        PasswordDisplayItem->resize(644, 148);
        verticalLayout = new QVBoxLayout(PasswordDisplayItem);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(PasswordDisplayItem);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(30, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        font.setPointSize(11);
        font.setBold(false);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        textBrowser = new QTextBrowser(PasswordDisplayItem);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMaximumSize(QSize(16777215, 70));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier New"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(true);
        textBrowser->setFont(font1);
        textBrowser->setMouseTracking(false);
        textBrowser->setReadOnly(false);
        textBrowser->setOverwriteMode(false);

        horizontalLayout->addWidget(textBrowser);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        changeBtn = new QPushButton(PasswordDisplayItem);
        changeBtn->setObjectName(QString::fromUtf8("changeBtn"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel Light"));
        font2.setPointSize(11);
        font2.setItalic(true);
        changeBtn->setFont(font2);

        horizontalLayout->addWidget(changeBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PasswordDisplayItem);

        QMetaObject::connectSlotsByName(PasswordDisplayItem);
    } // setupUi

    void retranslateUi(QWidget *PasswordDisplayItem)
    {
        PasswordDisplayItem->setWindowTitle(QCoreApplication::translate("PasswordDisplayItem", "Form", nullptr));
        label->setText(QCoreApplication::translate("PasswordDisplayItem", "TextLabel:", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("PasswordDisplayItem", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:14pt; font-weight:700; font-style:italic;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Corbel';\"><br /></p></body></html>", nullptr));
        changeBtn->setText(QCoreApplication::translate("PasswordDisplayItem", "Change", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswordDisplayItem: public Ui_PasswordDisplayItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDDISPLAYITEM_H
