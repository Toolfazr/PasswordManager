#include "AddPasswordWindow.h"
#include "ui_AddPasswordWindow.h"

AddPasswordWindow::AddPasswordWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddPasswordWindow)
{
    ui->setupUi(this);
}

AddPasswordWindow::~AddPasswordWindow()
{
    delete ui;
}

void AddPasswordWindow::work()
{
    this->show();
}

void AddPasswordWindow::on_workEndBtn_clicked()
{
    emit workEnd();
    this->hide();
    emit databaseInsert(ui->titleInput->text(),
                        ui->accountInput->text(),
                        ui->passwordInput->text());
}

void AddPasswordWindow::on_cancel_clicked()
{
    this->hide();
    emit addCancel();
}

void AddPasswordWindow::closeEvent(QCloseEvent *event) {
    emit addCancel();
    event->accept();
}
