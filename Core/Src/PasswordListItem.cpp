#include "PasswordListItem.h"
#include "ui_MainWindow.h"
#include "ui_PasswordListItem.h"
#include "MainWindow.h"

PasswordListItem::PasswordListItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PasswordListItem)
{
    ui->setupUi(this);
    this->raise();
    this->setStyleSheet("PasswordListItem{"
                   "border: 2px black;"
                        "}"
        );
    connect(this, &PasswordListItem::requestDelete, static_cast<MainWindow*>(parent), &MainWindow::deletePasswordListItem);
    connect(this, &PasswordListItem::requestAccess, static_cast<MainWindow*>(parent), &MainWindow::showPasswordDisplayItem);
    connect(this, &PasswordListItem::requestExport, static_cast<MainWindow*>(parent), &MainWindow::exportPassword);
}

PasswordListItem::~PasswordListItem()
{
    delete ui;
}

void PasswordListItem::on_Delete_clicked()
{
    emit requestDelete(this, id);
}

void PasswordListItem::on_Access_clicked()
{
    emit requestAccess(this);
}

void PasswordListItem::on_More_clicked()
{
    emit requestExport(id);
}

