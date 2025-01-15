#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ui_PasswordListItem.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , curId(0)
    , curAttr()
    , scene(new QGraphicsScene(this))
    , textItem(new QGraphicsTextItem())
{
    ui->setupUi(this);
    ui->topPwDisplayItem->hide();
    ui->topPwDisplayItem->setAttr("note");

    ui->midPwDisplayItem->hide();
    ui->midPwDisplayItem->setAttr("account");

    ui->bottomPwDisplayItem->hide();
    ui->bottomPwDisplayItem->setAttr("password");

    ui->graphicsView->setScene(scene);
    this->scene->setSceneRect(0, 0, 500, 400);
    QFont font("Corbel Light", 20);
    font.setItalic(true);
    textItem->setFont(font);
    textItem->setPos(100, 100);
    textItem->setPlainText("");
    this->scene->addItem(textItem);

    connect(ui->topPwDisplayItem, &PasswordDisplayItem::requestChange, this, &MainWindow::changePassword);
    connect(ui->midPwDisplayItem, &PasswordDisplayItem::requestChange, this, &MainWindow::changePassword);
    connect(ui->bottomPwDisplayItem, &PasswordDisplayItem::requestChange, this, &MainWindow::changePassword);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMainwindow()
{
    this->show();
}

void MainWindow::deletePasswordListItem(PasswordListItem* item, size_t id)
{
    ui->PasswordItemLayout->layout()->removeWidget(item);
    delete item;

    PasswordList.erase(
        std::remove(PasswordList.begin(), PasswordList.end(), item),
        PasswordList.end()
        );

    emit delPassword(id);
}

void MainWindow::on_AddNewPasswordBtn_clicked()
{
    this->setEnabled(false);
    emit addPasswordWindowWork();

}

void MainWindow::addPasswordWindowWorkEnd()
{
    this->setEnabled(true);
}

void MainWindow::appendPasswordListItem(size_t id, QString note)
{
    auto newItem = new PasswordListItem(this);
    newItem->setId(id);

    newItem->ui->label->setText(note);
    PasswordList.push_back(newItem);
    ui->PasswordItemLayout->addWidget(newItem);
}

void MainWindow::showPasswordDisplayItem(PasswordListItem* item)
{
    size_t id = item->getId();

    ui->graphicsView->hide();

    ui->topPwDisplayItem->show();
    ui->topPwDisplayItem->ui->label->setText("Note:");
    ui->topPwDisplayItem->ui->textBrowser->setText("loading");

    ui->midPwDisplayItem->show();
    ui->midPwDisplayItem->ui->label->setText("Account:");
    ui->midPwDisplayItem->ui->textBrowser->setText("loading");

    ui->bottomPwDisplayItem->show();
    ui->bottomPwDisplayItem->ui->label->setText("Password:");
    ui->bottomPwDisplayItem->ui->textBrowser->setText("loading");

    curId = id;
    emit accessPassword(id);
}

void MainWindow::updatePasswordDisplayItemData(QString note, QString account, QString password)
{
    ui->topPwDisplayItem->ui->textBrowser->setText(note);
    ui->topPwDisplayItem->ui->textBrowser->update();
    ui->midPwDisplayItem->ui->textBrowser->setText(account);
    ui->midPwDisplayItem->ui->textBrowser->update();
    ui->bottomPwDisplayItem->ui->textBrowser->setText(password);
    ui->bottomPwDisplayItem->ui->textBrowser->update();
}

void MainWindow::initPasswordList(std::unordered_map<size_t, QString> validId)
{
    for(auto& pair : validId)
    {
        appendPasswordListItem(pair.first, pair.second);
    }
}

void MainWindow::changePassword(PasswordDisplayItem* item)
{
    this->setEnabled(false);
    curAttr = item->attr;
    emit updateFormWork();
}

void MainWindow::updateRequestCancel()
{
    this->setEnabled(true);
}

void MainWindow::updateFormWorkEnd(QString str)
{
    this->setEnabled(true);
    emit updatePasswordDisplayItem(str, curAttr, curId);
}

void MainWindow::updatePasswordListItem(size_t id, QString note)
{
    for(auto& ptr : PasswordList)
    {
        if(ptr->id == id)
        {
            ptr->ui->label->setText(note);
            break;
        }
    }
}

void MainWindow::exportPassword(size_t id)
{
    emit startExportPassword(id);
}

void MainWindow::showMsg(QString str)
{
    textItem->setPlainText(str);

    ui->topPwDisplayItem->hide();
    ui->midPwDisplayItem->hide();
    ui->bottomPwDisplayItem->hide();
    ui->graphicsView->show();
    ui->graphicsView->update();
}

void MainWindow::tipOpenSerialFailed()
{
    showMsg("Fail to Open Serial");
}

void MainWindow::tipOpenSerialSuccess()
{
    showMsg("Open Serial Success");
}

void MainWindow::tipNoFingerVfy(int failTimes)
{
    showMsg(QString("Fail To Verify Finger for %1 Times").arg(failTimes));
}

void MainWindow::tipNeedRestart()
{
    showMsg("No Reaction, Suggest Restart This Application");
}

void MainWindow::tipFingerVfySuccess()
{
    showMsg("Finger Verify Success");
}

void MainWindow::on_connectBtn_clicked()
{
    emit checkSerialConnection();
}

