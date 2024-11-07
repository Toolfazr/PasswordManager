#include <QApplication>
#include "LoginDialog.h"
#include "MainWindow.h"
#include "ViewModel.h"
#include "UpdateInput.h"
#include "AddPasswordWindow.h"
#include "SerialWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;//输入主密码的窗口
    UpdateInput changeInput;//需要更改某一项时，接收更改后的字符串的窗口
    MainWindow w;//主窗口
    ViewModel vm;//处理与数据库间的交互
    AddPasswordWindow addWindow;//需要添加某一项时，接收各项数据输入的窗口
    SerialWindow serialWindow;//选择连接的串口以及处理串口数据收发的组件

    //根据主密码生成HashedKey后显示MainWindow
    //单击LoginDialog的Sure后发出showMainwindow与setHashedKey信号
    LoginDialog::connect(&login, &LoginDialog::showMainwindow, &w, &MainWindow::showMainwindow);

    LoginDialog::connect(&login, &LoginDialog::setHashedKey, &vm, &ViewModel::generateHashedKey);//generateHashedKey中初始化了DataBase
    //初始化PasswordList以及externIdTable
    ViewModel::connect(&vm, &ViewModel::dbInitEnd, &w, &MainWindow::initPasswordList);

    //添加一项密码
    //单击MainWindow的Add后发出addPasswordWindowWork信号
    MainWindow::connect(&w, &MainWindow::addPasswordWindowWork, &addWindow, [&addWindow](){addWindow.show();});

    //单击AddPasswordWindow的sure后发出databaseInsert和workEnd信号
    AddPasswordWindow::connect(&addWindow, &AddPasswordWindow::workEnd, &w, [&w](){w.setEnabled(true);});

    AddPasswordWindow::connect(&addWindow, &AddPasswordWindow::databaseInsert, &vm, &ViewModel::addSlot);
    ViewModel::connect(&vm, &ViewModel::addEnd, &w, &MainWindow::appendPasswordListItem);

    //如果单击AddPasswordWindow的Cancel或将其关闭，分别发出addCancel、destroyed信号
    AddPasswordWindow::connect(&addWindow, &AddPasswordWindow::destroyed, &w, [&w](){w.setEnabled(true);});
    AddPasswordWindow::connect(&addWindow, &AddPasswordWindow::addCancel, &w, [&w](){w.setEnabled(true);});

    //删除一项密码
    //单击PasswordListItem的Delete后，MainWindow向外发出delPassword信号
    MainWindow::connect(&w, &MainWindow::delPassword, &vm, &ViewModel::delSlot);

    //查看一项密码
    //单击PasswordListItem的Access后，MainWindow向外发出accessPassword信号
    MainWindow::connect(&w, &MainWindow::accessPassword, &vm, &ViewModel::handleAccess);
    ViewModel::connect(&vm, &ViewModel::accessEnd, &w, &MainWindow::updatePasswordDisplayItemData);

    //修改一项密码
    //单击PasswordDispalyItem的Change后，MainWindow向外发出updateFormWork信号
    MainWindow::connect(&w, &MainWindow::updateFormWork, &changeInput, &UpdateInput::UpdateFormShow);
    UpdateInput::connect(&changeInput, &UpdateInput::inputEnd, &w, &MainWindow::updateFormWorkEnd);
    MainWindow::connect(&w, &MainWindow::updatePasswordDisplayItem, &vm, &ViewModel::updateSlot);
    ViewModel::connect(&vm, &ViewModel::updateEnd, &w, [&w](size_t id){emit w.accessPassword(id);});
    //MainWindow::connect(&w, &MainWindow::accessPassword, &vm, &ViewModel::handleAccess);
    //ViewModel::connect(&vm, &ViewModel::accessEnd, &w, &MainWindow::updatePasswordDisplayItemDSata);

    //如果一项密码的Note被更改，那么PasswordList中该项密码的Note同样要更改，此时ViewModel发出updatePasswordListItemNote信号
    ViewModel::connect(&vm, &ViewModel::updatePasswordListItemNote, &w, &MainWindow::updatePasswordListItem);

    //重写了CloseEvent事件，如果UpdateInput被关闭或Cancel，都会发出noInput信号
    UpdateInput::connect(&changeInput, &UpdateInput::noInput, &w, &MainWindow::updateRequestCancel);

    //处理串口连接
    //单击connect后，进入串口连接界面
    MainWindow::connect(&w, &MainWindow::checkSerialConnection, &serialWindow, &SerialWindow::connectPort);
    SerialWindow::connect(&serialWindow, &SerialWindow::connectIsOk, &w, [&w](){w.setEnabled(true);});
    SerialWindow::connect(&serialWindow, &SerialWindow::disconnected, &vm, [&vm](){vm.setSerialState(false);});
    SerialWindow::connect(&serialWindow, &SerialWindow::connectFail, &w, &MainWindow::tipOpenSerialFailed);
    SerialWindow::connect(&serialWindow, &SerialWindow::connectFail, &vm, [&vm](){vm.setSerialState(false);});
    SerialWindow::connect(&serialWindow, &SerialWindow::connectSuccess, &w, &MainWindow::tipOpenSerialSuccess);
    SerialWindow::connect(&serialWindow, &SerialWindow::connectSuccess, &vm, [&vm](){vm.setSerialState(true);});

    //串口数据的发送与接收
    ViewModel::connect(&vm, &ViewModel::packetIsReady, &serialWindow, &SerialWindow::writeData);
    SerialWindow::connect(&serialWindow, &SerialWindow::recPacketEnd, &vm, &ViewModel::getAck);

    //export一项密码
    MainWindow::connect(&w, &MainWindow::startExportPassword, &vm, &ViewModel::handleExport);

    //根据收到的Ack显示提示信息
    ViewModel::connect(&vm, &ViewModel::noFingerVfy, &w, &MainWindow::tipNoFingerVfy);
    ViewModel::connect(&vm, &ViewModel::fingerVfySuccess, &w, &MainWindow::tipFingerVfySuccess);
    ViewModel::connect(&vm, &ViewModel::noAvailableSerial, &w, &MainWindow::tipOpenSerialFailed);
    ViewModel::connect(&vm, &ViewModel::doingLastExternOperation, &w, &MainWindow::tipNeedRestart);

    login.show();
    return a.exec();
}
