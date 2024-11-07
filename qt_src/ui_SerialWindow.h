/********************************************************************************
** Form generated from reading UI file 'SerialWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALWINDOW_H
#define UI_SERIALWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *cancel;

    void setupUi(QWidget *SerialWindow)
    {
        if (SerialWindow->objectName().isEmpty())
            SerialWindow->setObjectName(QString::fromUtf8("SerialWindow"));
        SerialWindow->resize(492, 185);
        SerialWindow->setMinimumSize(QSize(492, 185));
        SerialWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 242, 238);\n"
"border: 0px;"));
        verticalLayout = new QVBoxLayout(SerialWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(SerialWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        comboBox = new QComboBox(SerialWindow);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(250, 22));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Corbel"));
        font1.setPointSize(10);
        comboBox->setFont(font1);

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(SerialWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel Light"));
        font2.setPointSize(11);
        font2.setItalic(true);
        pushButton->setFont(font2);

        horizontalLayout->addWidget(pushButton);

        cancel = new QPushButton(SerialWindow);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setFont(font2);

        horizontalLayout->addWidget(cancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SerialWindow);

        QMetaObject::connectSlotsByName(SerialWindow);
    } // setupUi

    void retranslateUi(QWidget *SerialWindow)
    {
        SerialWindow->setWindowTitle(QCoreApplication::translate("SerialWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("SerialWindow", "Choose Serial:", nullptr));
        pushButton->setText(QCoreApplication::translate("SerialWindow", "Sure", nullptr));
        cancel->setText(QCoreApplication::translate("SerialWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialWindow: public Ui_SerialWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALWINDOW_H
