#include "AccessItem.h"
#include "ui_AccessItem.h"

AccessItem::AccessItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccessItem)
{
    ui->setupUi(this);
}

AccessItem::~AccessItem()
{
    delete ui;
}
