#ifndef SERIALWINDOW_H
#define SERIALWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

namespace Ui {
class SerialWindow;
}

class SerialWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SerialWindow(QWidget *parent = nullptr);
    ~SerialWindow();
signals:
    void connectIsOk();
    void connectSuccess();
    void connectFail();
    void disconnected();
    void recPacketEnd(QByteArray packet);
public slots:
    void connectPort();
    void writeData(QByteArray packet);
private slots:
    void on_pushButton_clicked();
    void on_cancel_clicked();
    void readData();
    void detectReadEnd();

private:
    void closeEvent(QCloseEvent* event);
    void connectToSerial();
    Ui::SerialWindow *ui;
    bool serialIsConnected;
    QList<QSerialPortInfo> ports;
    QSerialPort* serial;
    QByteArray* data;
    const unsigned char END_FLAG = 0XED;
};

#endif // SERIALWINDOW_H
