#include "PasswordDisplayItem.h"
#include "ui_PasswordDisplayItem.h"

PasswordDisplayItem::PasswordDisplayItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PasswordDisplayItem)
{
    ui->setupUi(this);
}

PasswordDisplayItem::~PasswordDisplayItem()
{
    delete ui;
}

void PasswordDisplayItem::on_changeBtn_clicked()
{
    emit requestChange(this);
}

