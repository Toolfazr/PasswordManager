#include "UpdateInput.h"
#include "ui_UpdateInput.h"

UpdateInput::UpdateInput(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateInput)
{
    ui->setupUi(this);
}

UpdateInput::~UpdateInput()
{
    delete ui;
}

void UpdateInput::UpdateFormShow()
{
    this->show();
}

void UpdateInput::closeEvent(QCloseEvent* event)
{
    emit noInput();
    event->accept();
    this->hide();
}

void UpdateInput::on_OK_clicked()
{
    QString str = ui->textEdit->toPlainText();
    this->hide();
    emit inputEnd(str);
}


void UpdateInput::on_Cancel_clicked()
{
    emit noInput();
    this->hide();
}

