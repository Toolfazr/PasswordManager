#include "SerialWindow.h"
#include "ui_SerialWindow.h"

SerialWindow::SerialWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialWindow)
    , serialIsConnected(false)
    , serial(NULL)
    , data(NULL)
{
    ui->setupUi(this);

    connect(this, &SerialWindow::connectSuccess, this, [](){qDebug() << "success";});
    connect(this, &SerialWindow::connectFail, this, [](){qDebug() << "fail";});
}

SerialWindow::~SerialWindow()
{
    delete ui;
}

void SerialWindow::connectPort()
{
    if(!serialIsConnected)
    {
        //读取串口信息
        const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for(auto& port : ports)
        {
            ui->comboBox->addItem(port.portName() + " - " + port.description());
        }
        this->show();
    }
    else
    {
        emit connectIsOk();
    }

}

void SerialWindow::connectToSerial()
{
    //得到正确的串口名称
    QString selectedPort = ui->comboBox->currentText();
    int index = selectedPort.indexOf(" ");
    selectedPort = selectedPort.left(index);

    if(serial != nullptr)
    {
        delete serial;
        serial = nullptr;
    }
    serial = new QSerialPort(selectedPort);

    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::TwoStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite))
    {
        serialIsConnected = true;
        connect(serial, &QSerialPort::readyRead, this, &SerialWindow::readData);
        connect(serial, &QSerialPort::errorOccurred, this, [&](){emit disconnected();});
        emit connectSuccess();
    }
    else
    {
        serialIsConnected = false;
        emit connectFail();
    }
}

void SerialWindow::on_pushButton_clicked()
{
    connectToSerial();
    this->hide();
    emit connectIsOk();
}

void SerialWindow::closeEvent(QCloseEvent* event)
{
    emit connectIsOk();
    this->hide();
}

void SerialWindow::on_cancel_clicked()
{
    emit connectIsOk();
    this->hide();
}

void SerialWindow::readData()
{
    // 开始接收
    if (!data)
    {
        data = new QByteArray();
    }

    *data += serial->readAll();

    // 确保data至少有一个字节
    if (!data->isEmpty() && (unsigned char)data->back() == END_FLAG)
    {
        // 在detectReadEnd中判断是否真正结束
        QTimer::singleShot(50, this, &SerialWindow::detectReadEnd);
    }
}

void SerialWindow::detectReadEnd()
{
    if (serial->bytesAvailable() == 0)
    {
        QByteArray tempData(*data);
        tempData.chop(1);  // 去掉END_FLAG
        QByteArray packet(tempData);
        emit recPacketEnd(packet);

        delete data;
        data = nullptr;
    }
}

void SerialWindow::writeData(QByteArray data)
{
    if (serial->isOpen())
    {
        qint64 bytesWritten = serial->write(data);
        if (bytesWritten == -1)
        {
            //empty
        }
        else
        {
            //empty
        }
    }
    else
    {
        //empty
    }
}
