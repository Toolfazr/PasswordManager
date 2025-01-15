/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <PasswordDisplayItem.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *PasswordItemLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *AddNewPasswordBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *connectBtn;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    PasswordDisplayItem *topPwDisplayItem;
    PasswordDisplayItem *midPwDisplayItem;
    PasswordDisplayItem *bottomPwDisplayItem;
    QPlainTextEdit *basePlainText;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1080, 500);
        MainWindow->setMinimumSize(QSize(1080, 500));
        MainWindow->setMaximumSize(QSize(1080, 500));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Serif"));
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 242, 238);\n"
"border: 0px;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        centralwidget->setStyleSheet(QString::fromUtf8("border: 0px;"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(500, 242));
        scrollArea->setMaximumSize(QSize(768, 16777215));
        scrollArea->setContextMenuPolicy(Qt::DefaultContextMenu);
        scrollArea->setStyleSheet(QString::fromUtf8("border: 0px;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 519, 482));
        scrollAreaWidgetContents_2->setCursor(QCursor(Qt::ArrowCursor));
        scrollAreaWidgetContents_2->setStyleSheet(QString::fromUtf8("border: 0px;"));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        PasswordItemLayout = new QVBoxLayout();
        PasswordItemLayout->setSpacing(0);
        PasswordItemLayout->setObjectName(QString::fromUtf8("PasswordItemLayout"));

        verticalLayout->addLayout(PasswordItemLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(220, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        AddNewPasswordBtn = new QPushButton(scrollAreaWidgetContents_2);
        AddNewPasswordBtn->setObjectName(QString::fromUtf8("AddNewPasswordBtn"));
        AddNewPasswordBtn->setMinimumSize(QSize(50, 50));
        AddNewPasswordBtn->setMaximumSize(QSize(50, 50));
        AddNewPasswordBtn->setStyleSheet(QString::fromUtf8("background-image: url(\":/pics/lus.png\");\n"
"background-color: rgb(243,242,238);\n"
"background-repeat: no-repeat; \n"
"background-position: center; \n"
"border: 3px solid rgb(195, 195, 195);\n"
"border-radius: 25;\n"
"padding: 10px; \n"
"font-size: 16px; \n"
"color: rgb(195, 195, 195); \n"
""));

        horizontalLayout_2->addWidget(AddNewPasswordBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        connectBtn = new QPushButton(scrollAreaWidgetContents_2);
        connectBtn->setObjectName(QString::fromUtf8("connectBtn"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Corbel Light"));
        font1.setPointSize(11);
        font1.setItalic(true);
        connectBtn->setFont(font1);

        horizontalLayout_2->addWidget(connectBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout->addWidget(scrollArea);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(1, 1));
        line->setMaximumSize(QSize(1, 16777215));
        line->setStyleSheet(QString::fromUtf8("border-left: 2px dashed black; "));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(500, 0));
        widget->setStyleSheet(QString::fromUtf8("border: 0px;"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        topPwDisplayItem = new PasswordDisplayItem(widget);
        topPwDisplayItem->setObjectName(QString::fromUtf8("topPwDisplayItem"));

        verticalLayout_2->addWidget(topPwDisplayItem);

        midPwDisplayItem = new PasswordDisplayItem(widget);
        midPwDisplayItem->setObjectName(QString::fromUtf8("midPwDisplayItem"));

        verticalLayout_2->addWidget(midPwDisplayItem);

        bottomPwDisplayItem = new PasswordDisplayItem(widget);
        bottomPwDisplayItem->setObjectName(QString::fromUtf8("bottomPwDisplayItem"));

        verticalLayout_2->addWidget(bottomPwDisplayItem);

        basePlainText = new QPlainTextEdit(widget);
        basePlainText->setObjectName(QString::fromUtf8("basePlainText"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel Light"));
        font2.setPointSize(20);
        font2.setItalic(true);
        basePlainText->setFont(font2);
        basePlainText->setReadOnly(true);

        verticalLayout_2->addWidget(basePlainText);


        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        AddNewPasswordBtn->setText(QString());
        connectBtn->setText(QCoreApplication::translate("MainWindow", "Connect to Serial", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
