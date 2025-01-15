#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QCryptographicHash>
#include <QByteArray>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:

    void on_pushButton_clicked();

signals:
    void showMainwindow();
    void setHashedKey(QString str);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
