#ifndef ADDPASSWORDWINDOW_H
#define ADDPASSWORDWINDOW_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class AddPasswordWindow;
}

class AddPasswordWindow : public QWidget
{
    Q_OBJECT
signals:
    void workEnd();
    void addCancel();
    void databaseInsert(QString note, QString account, QString password);
public:
    explicit AddPasswordWindow(QWidget *parent = nullptr);
    ~AddPasswordWindow();
public slots:
    void work();
private slots:

    void on_workEndBtn_clicked();
    void on_cancel_clicked();

private:
    void closeEvent(QCloseEvent *event);
    Ui::AddPasswordWindow *ui;
};

#endif // ADDPASSWORDWINDOW_H
