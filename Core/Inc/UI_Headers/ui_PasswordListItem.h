/********************************************************************************
** Form generated from reading UI file 'PasswordListItem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDLISTITEM_H
#define UI_PASSWORDLISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasswordListItem
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Access;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *Delete;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *More;
    QSpacerItem *horizontalSpacer;
    QFrame *line;

    void setupUi(QWidget *PasswordListItem)
    {
        if (PasswordListItem->objectName().isEmpty())
            PasswordListItem->setObjectName(QString::fromUtf8("PasswordListItem"));
        PasswordListItem->resize(757, 100);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PasswordListItem->sizePolicy().hasHeightForWidth());
        PasswordListItem->setSizePolicy(sizePolicy);
        PasswordListItem->setMinimumSize(QSize(0, 90));
        PasswordListItem->setMaximumSize(QSize(1400, 100));
        PasswordListItem->setCursor(QCursor(Qt::ArrowCursor));
        PasswordListItem->setToolTipDuration(0);
        PasswordListItem->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(PasswordListItem);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(PasswordListItem);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 0));
        label->setMaximumSize(QSize(150, 32));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(174, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Access = new QPushButton(PasswordListItem);
        Access->setObjectName(QString::fromUtf8("Access"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Corbel Light"));
        font1.setPointSize(11);
        font1.setItalic(true);
        Access->setFont(font1);

        horizontalLayout->addWidget(Access);

        horizontalSpacer_4 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        Delete = new QPushButton(PasswordListItem);
        Delete->setObjectName(QString::fromUtf8("Delete"));
        Delete->setFont(font1);

        horizontalLayout->addWidget(Delete);

        horizontalSpacer_3 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        More = new QPushButton(PasswordListItem);
        More->setObjectName(QString::fromUtf8("More"));
        More->setMaximumSize(QSize(16777215, 16777215));
        More->setFont(font1);

        horizontalLayout->addWidget(More);

        horizontalSpacer = new QSpacerItem(155, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(PasswordListItem);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(0, 1));
        line->setStyleSheet(QString::fromUtf8("border-top: 1px solid rgb(197, 197, 197);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        retranslateUi(PasswordListItem);

        QMetaObject::connectSlotsByName(PasswordListItem);
    } // setupUi

    void retranslateUi(QWidget *PasswordListItem)
    {
        PasswordListItem->setWindowTitle(QCoreApplication::translate("PasswordListItem", "Form", nullptr));
        label->setText(QCoreApplication::translate("PasswordListItem", "loading", nullptr));
        Access->setText(QCoreApplication::translate("PasswordListItem", "Access", nullptr));
        Delete->setText(QCoreApplication::translate("PasswordListItem", "Delete", nullptr));
        More->setText(QCoreApplication::translate("PasswordListItem", "Export", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswordListItem: public Ui_PasswordListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDLISTITEM_H
