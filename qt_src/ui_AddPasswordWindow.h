/********************************************************************************
** Form generated from reading UI file 'AddPasswordWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPASSWORDWINDOW_H
#define UI_ADDPASSWORDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddPasswordWindow
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QLabel *account;
    QLabel *password;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *titleInput;
    QLineEdit *accountInput;
    QLineEdit *passwordInput;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *workEndBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancel;

    void setupUi(QWidget *AddPasswordWindow)
    {
        if (AddPasswordWindow->objectName().isEmpty())
            AddPasswordWindow->setObjectName(QString::fromUtf8("AddPasswordWindow"));
        AddPasswordWindow->resize(375, 142);
        AddPasswordWindow->setMaximumSize(QSize(375, 142));
        AddPasswordWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 242, 238);\n"
"border: 0px;"));
        verticalLayout_4 = new QVBoxLayout(AddPasswordWindow);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title = new QLabel(AddPasswordWindow);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        font.setPointSize(12);
        font.setBold(true);
        title->setFont(font);

        verticalLayout->addWidget(title);

        account = new QLabel(AddPasswordWindow);
        account->setObjectName(QString::fromUtf8("account"));
        account->setFont(font);

        verticalLayout->addWidget(account);

        password = new QLabel(AddPasswordWindow);
        password->setObjectName(QString::fromUtf8("password"));
        password->setFont(font);

        verticalLayout->addWidget(password);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        titleInput = new QLineEdit(AddPasswordWindow);
        titleInput->setObjectName(QString::fromUtf8("titleInput"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier New"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        titleInput->setFont(font1);
        titleInput->setStyleSheet(QString::fromUtf8("background-color: rgb(197, 197, 197);"));

        verticalLayout_2->addWidget(titleInput);

        accountInput = new QLineEdit(AddPasswordWindow);
        accountInput->setObjectName(QString::fromUtf8("accountInput"));
        accountInput->setFont(font1);
        accountInput->setStyleSheet(QString::fromUtf8("background-color: rgb(197, 197, 197);"));

        verticalLayout_2->addWidget(accountInput);

        passwordInput = new QLineEdit(AddPasswordWindow);
        passwordInput->setObjectName(QString::fromUtf8("passwordInput"));
        passwordInput->setFont(font1);
        passwordInput->setStyleSheet(QString::fromUtf8("background-color: rgb(197, 197, 197);"));

        verticalLayout_2->addWidget(passwordInput);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        workEndBtn = new QPushButton(AddPasswordWindow);
        workEndBtn->setObjectName(QString::fromUtf8("workEndBtn"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel Light"));
        font2.setPointSize(11);
        font2.setItalic(true);
        workEndBtn->setFont(font2);

        horizontalLayout_2->addWidget(workEndBtn);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        cancel = new QPushButton(AddPasswordWindow);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setFont(font2);

        horizontalLayout_2->addWidget(cancel);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(AddPasswordWindow);

        QMetaObject::connectSlotsByName(AddPasswordWindow);
    } // setupUi

    void retranslateUi(QWidget *AddPasswordWindow)
    {
        AddPasswordWindow->setWindowTitle(QCoreApplication::translate("AddPasswordWindow", "Form", nullptr));
        title->setText(QCoreApplication::translate("AddPasswordWindow", "title:", nullptr));
        account->setText(QCoreApplication::translate("AddPasswordWindow", "account:", nullptr));
        password->setText(QCoreApplication::translate("AddPasswordWindow", "password:", nullptr));
        workEndBtn->setText(QCoreApplication::translate("AddPasswordWindow", "OK", nullptr));
        cancel->setText(QCoreApplication::translate("AddPasswordWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddPasswordWindow: public Ui_AddPasswordWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPASSWORDWINDOW_H
