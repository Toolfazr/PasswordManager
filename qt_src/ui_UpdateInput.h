/********************************************************************************
** Form generated from reading UI file 'UpdateInput.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEINPUT_H
#define UI_UPDATEINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UpdateInput
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *OK;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Cancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *UpdateInput)
    {
        if (UpdateInput->objectName().isEmpty())
            UpdateInput->setObjectName(QString::fromUtf8("UpdateInput"));
        UpdateInput->resize(415, 101);
        UpdateInput->setMaximumSize(QSize(415, 101));
        UpdateInput->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 242, 238);\n"
"border: 0px;"));
        verticalLayout = new QVBoxLayout(UpdateInput);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(UpdateInput);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        textEdit = new QTextEdit(UpdateInput);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier New"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setItalic(true);
        textEdit->setFont(font1);
        textEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(197, 197, 197);"));

        horizontalLayout_2->addWidget(textEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(10, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        OK = new QPushButton(UpdateInput);
        OK->setObjectName(QString::fromUtf8("OK"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel Light"));
        font2.setPointSize(11);
        font2.setItalic(true);
        OK->setFont(font2);

        horizontalLayout->addWidget(OK);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Cancel = new QPushButton(UpdateInput);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setFont(font2);

        horizontalLayout->addWidget(Cancel);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(UpdateInput);

        QMetaObject::connectSlotsByName(UpdateInput);
    } // setupUi

    void retranslateUi(QDialog *UpdateInput)
    {
        UpdateInput->setWindowTitle(QCoreApplication::translate("UpdateInput", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("UpdateInput", "Change to", nullptr));
        OK->setText(QCoreApplication::translate("UpdateInput", "OK", nullptr));
        Cancel->setText(QCoreApplication::translate("UpdateInput", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UpdateInput: public Ui_UpdateInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEINPUT_H
