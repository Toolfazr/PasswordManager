#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "PasswordListItem.h"
#include "PasswordDisplayItem.h"
#include "ui_PasswordDisplayItem.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class PasswordListItem;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void addPasswordWindowWork();
    void delPassword(size_t id);
    void accessPassword(size_t id);
    void accessNote(size_t id);
    void updateFormWork();
    void updatePasswordDisplayItem(QString str, QString attr, size_t id);
    void startExportPassword(size_t id);
    void checkSerialConnection();
private slots:
    void on_AddNewPasswordBtn_clicked();
    void on_connectBtn_clicked();

public slots:
    void showMainwindow();
    void addPasswordWindowWorkEnd();
    void deletePasswordListItem(PasswordListItem* item, size_t id);
    void appendPasswordListItem(size_t id, QString note);
    void showPasswordDisplayItem(PasswordListItem* item);
    void updatePasswordDisplayItemData(QString note, QString account, QString password);
    void initPasswordList(std::unordered_map<size_t, QString> validId);
    void changePassword(PasswordDisplayItem* item);
    void updateFormWorkEnd(QString str);
    void updateRequestCancel();
    void updatePasswordListItem(size_t id, QString note);
    void exportPassword(size_t id);
    void tipOpenSerialFailed();
    void tipOpenSerialSuccess();
    void tipNoFingerVfy(int failTimes);
    void tipNeedRestart();
    void tipFingerVfySuccess();
private:
    Ui::MainWindow *ui;
    size_t curId;//单击一项密码的Access时确定
    QString curAttr;//单击一项密码的Access后出现Change选项，进一步确定curAttr
    std::vector<PasswordListItem*> PasswordList;
    QGraphicsScene* scene;
    QGraphicsTextItem* textItem;

    void showMsg(QString str);
};
#endif // MAINWINDOW_H
