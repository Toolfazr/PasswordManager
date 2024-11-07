#include "AccessWindow.h"
#include "ui_AccessWindow.h"

AccessWindow::AccessWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccessWindow)
{
    ui->setupUi(this);
}

AccessWindow::~AccessWindow()
{
    delete ui;
}
