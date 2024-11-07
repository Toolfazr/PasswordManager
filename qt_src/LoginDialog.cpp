#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->DialogFrame->setFrameShadow(QFrame::Plain);
    ui->DialogFrame->setFrameStyle(QFrame::Box);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    this->hide();
    emit showMainwindow();
    emit setHashedKey(ui->lineEdit->text());
}

