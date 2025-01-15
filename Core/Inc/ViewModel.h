#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "BytesModel.h"
#include <QCryptographicHash>
#include <QtCrypto>

class ViewModel: public QObject
{
Q_OBJECT
signals:
    void addEnd(size_t id, QString note);
    void accessEnd(QString note, QString account, QString password);
    void updateEnd(size_t id);
    void dbInitEnd(std::unordered_map<size_t, QString> validId);
    void updatePasswordListItemNote(size_t id, QString note);
    void packetIsReady(QByteArray packet);

    void noFingerVfy(int failTimes);
    void fingerVfySuccess();
    void storeSuccess(size_t id);
    void deleteSuccess();
    void externSuccess(size_t id);

    void noAvailableSerial();
    void doingLastExternOperation();
public:
    ViewModel();
    bool initDb();
    int insert(QString str, QString attr);
    bool update(QString str, QString attr, size_t id);
    bool del(size_t id);
    QString select(QString attr, size_t id);
    inline bool getDataBaseInitState()
    {
        return dataBaseInitState;
    }
    inline void setSerialState(bool state)
    {
        serialIsReady = state;
    }

public slots:
    void initDbSlot();
    void addSlot(QString note, QString account, QString password);
    void insertSlot(QString str, QString attr);
    void updateSlot(QString str, QString attr, size_t id);
    void delSlot(size_t id);
    void handleAccess(size_t id);
    void generateHashedKey(QString str);
    void handleExport(size_t id);
    void getAck(QByteArray ack);

private slots:
    void localDelete();
private:
    int fingerVfyFailedTimes;
    bool serialIsReady;
    std::vector<size_t> externIdTable;
    BytesModel model;
    bool dataBaseInitState;
    QByteArray strEncryption(QString& str);
    QString strDecryption(QByteArray bytes);
    QByteArray hashedKey;
    bool hashedKeyIsReady;
    const unsigned int ID_TO_POS = 64;
    QByteArray idToPosBytes(size_t id);
    unsigned short posBytesToPos(QByteArray bytes);
    void setIdExported(size_t id);

    size_t externingId;
    size_t accessingId;
    //接收到的应答位及其之后数据
    const uint8_t NO_FINGER_VFY = 0X00;//Only ACK
    const uint8_t PASSWORD_DATA = 0X01;//ACK + PASSWORD_DATA
    const uint8_t DELETE_SUCCESS = 0X02;//Only ACK
    const uint8_t STORE_SUCCESS = 0X03;//ACK + PASSWORD_DATA

    QByteArray iv;//加密所需的初始化向量
};

#endif // VIEWMODEL_H
