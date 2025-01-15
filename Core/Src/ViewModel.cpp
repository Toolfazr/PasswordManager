#include "ViewModel.h"
#include <QDebug>

ViewModel::ViewModel():
    fingerVfyFailedTimes(0),
    serialIsReady(false),
    dataBaseInitState(false),
    hashedKeyIsReady(false),
    externingId(0X00),
    accessingId(0X00)
{
    connect(this, &ViewModel::storeSuccess, this, &ViewModel::localDelete);

    QCA::init();
    iv = QByteArray(16, 0);
}

bool ViewModel::initDb()
{
    dataBaseInitState = model.initDb();
    return dataBaseInitState;
}

int ViewModel::insert(QString str, QString attr)
{
    if(dataBaseInitState)
    {
        QByteArray bytes = strEncryption(str);
        return model.bytesInsert(bytes, attr);
    }

    return -1;
}

bool ViewModel::update(QString str, QString attr, size_t id)
{
    if(dataBaseInitState)
    {
        QByteArray bytes = strEncryption(str);
        return model.bytesUpdate(bytes, attr, id);
    }

    return false;
}

bool ViewModel::del(size_t id)
{
    if(dataBaseInitState)
    {
        return model.bytesDelete(id);
    }

    return false;
}

QString ViewModel::select(QString attr, size_t id)
{
    if(dataBaseInitState)
    {
        QByteArray bytes = model.bytesSelect(id, attr);
        QString str = QString::fromUtf8(bytes);
        return str;
    }

    return QString();
}

void ViewModel::insertSlot(QString str, QString attr)
{
  if(insert(str, attr) == -1)
    {
        //empty
    }
}

void ViewModel::updateSlot(QString str, QString attr, size_t id)
{
    //如果id未被extern或者update的不是password,则访问SQLite
    auto it = std::find(externIdTable.begin(), externIdTable.end(), id);
    if((it == externIdTable.end()) || (attr != "password"))
    {
        if(!update(str, attr, id))
        {
            //empty
        }
        else
        {
            emit updateEnd(id);
            if(attr == "note")
                emit updatePasswordListItemNote(id, str);
        }
    }
    //否则访问串口
    else
    {
        //串口此时应该可用
        if(serialIsReady)
        {
            //此时应该没有其它Password被extern
            if(externingId == 0X00)
            {
                qDebug() << "send update packet";
                externingId = id;
                unsigned short pos = posBytesToPos(model.bytesSelect(id, "externPos"));
                qDebug() << "update id is :" << id;

                QByteArray packet;
                packet.append((unsigned char)(pos >> 8)&0XFF);
                packet.append((unsigned char)(pos&0XFF));
                packet.append((unsigned char)(0X01 << 2));
                QByteArray bytes = strEncryption(str);

                packet.append((unsigned char)(0X01 + bytes.length()));
                packet += bytes;

                emit packetIsReady(packet);
            }
            else
            {
                emit doingLastExternOperation();
            }
        }
        else
        {
            emit noAvailableSerial();
        }

    }
}

void ViewModel::delSlot(size_t id)
{
    if(!del(id))
    {
        //empty
    }
}

void ViewModel::initDbSlot()
{
    if(!initDb())
    {
        //empty
    }
    else
    {
        std::unordered_map<size_t, QByteArray> bytesTable = model.getAllValidIdWithNote();
        std::unordered_map<size_t, QString> strTable;
        //获取所有Password以及被Extern的Password
        for(auto& pair : bytesTable)
        {
            strTable.insert({pair.first, strDecryption(pair.second)});
            if(model.bytesSelect(pair.first, "externPos") != "0")
            {
                externIdTable.push_back(pair.first);
            }
        }

        emit dbInitEnd(strTable);
    }
}

void ViewModel::addSlot(QString note, QString account, QString password)
{
    QByteArray noteBytes = strEncryption(note);
    QByteArray accountBytes = strEncryption(account);
    QByteArray passwordBytes = strEncryption(password);
    QString externIdStr = "0";
    QByteArray externIdBytes = externIdStr.toUtf8();

    size_t id = model.bytesInsert(noteBytes, "note");
    model.bytesUpdate(accountBytes, "account", id);
    model.bytesUpdate(passwordBytes, "password", id);
    model.bytesUpdate(externIdBytes, "externPos", id);

    emit addEnd(id, note);
}

QByteArray ViewModel::strEncryption(QString& str)
{
    // 确保密钥长度为 256 位（32 字节）
    QByteArray key = hashedKey;
    if (key.size() != 32)
    {
        return QByteArray();
    }

    QCA::Cipher cipher("aes256", QCA::Cipher::CBC, QCA::Cipher::Padding::PKCS7, QCA::Direction::Encode, key, iv);
    QByteArray inputData = str.toUtf8();
    QByteArray encryptedData;
    const int blockSize = 16;

    // 逐块加密数据
    for (int i = 0; i < inputData.size(); i += blockSize)
    {
        int chunkSize = qMin(blockSize, inputData.size() - i);
        QByteArray chunk = inputData.mid(i, chunkSize);
        encryptedData.append(cipher.update(chunk).toByteArray());
    }

    // 完成加密
    encryptedData.append(cipher.final().toByteArray());

    return encryptedData;
}

QString ViewModel::strDecryption(QByteArray bytes)
{
    // 确保密钥长度为 256 位（32 字节）
    QByteArray key = hashedKey;
    if (key.size() != 32)
    {

        return QString();
    }

    // 初始化 QCA
    QCA::Cipher cipher("aes256", QCA::Cipher::CBC, QCA::Cipher::Padding::PKCS7, QCA::Direction::Decode, key, iv);

    QByteArray decryptedData;
    const int blockSize = 16;
    int dataSize = bytes.size();

    // 逐块解密数据
    for (int i = 0; i < dataSize; i += blockSize)
    {
        int chunkSize = qMin(blockSize, dataSize - i);
        QByteArray chunk = bytes.mid(i, chunkSize);
        decryptedData.append(cipher.update(chunk).toByteArray());
    }

    // 完成解密
    decryptedData.append(cipher.final().toByteArray());

    // 返回解密后的字符串
    return QString::fromUtf8(decryptedData);
}

void ViewModel::handleAccess(size_t id)
{
    //如果id未被extern,则访问SQLite
    auto it = std::find(externIdTable.begin(), externIdTable.end(), id);
    if(it == externIdTable.end())
    {
        QString note = strDecryption(model.bytesSelect(id, "note"));
        QString account = strDecryption(model.bytesSelect(id, "account"));
        QString password = strDecryption(model.bytesSelect(id, "password"));
        qDebug() << "Get note, account, password from sqlite: " << note << account << password;
        emit accessEnd(note, account, password);
    }
    //否则访问串口
    else
    {
        //此时没有其它存储到外部的password正在被访问
        if(accessingId != 0X00)
        {
            emit doingLastExternOperation();
        }
        else
        {
            if(serialIsReady)
            {
                accessingId = id;
                unsigned short pos = posBytesToPos(model.bytesSelect(id, "externPos"));
                QByteArray packet;
                packet.append((unsigned char)(pos >> 8)&0XFF);
                packet.append((unsigned char)(pos&0XFF));
                packet.append((unsigned char)(0X01 << 1));
                packet.append((unsigned char)0X01);
                emit packetIsReady(packet);
            }
            else
            {
                emit noAvailableSerial();
            }
        }
    }
}

void ViewModel::generateHashedKey(QString str)
{
    hashedKey = QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Sha256);
    // 确保密钥长度符合 AES 的要求（例如 256 位的 AES）
    if (hashedKey.size() > 32) {
        hashedKey = hashedKey.left(32);  // 截断为 256 位
    } else if (hashedKey.size() < 32) {
        // 如果需要，可以填充密钥（这通常不是推荐的做法）
        hashedKey.append(QByteArray(32 - hashedKey.size(), '\0'));
    }
    hashedKeyIsReady = true;
    initDbSlot();
}

void ViewModel::setIdExported(size_t id)
{
    if(model.bytesUpdate(idToPosBytes(id), "externPos", id))
    {
        externIdTable.push_back(id);
    }
}

QByteArray ViewModel::idToPosBytes(size_t id)
{
    QString posStr = QString::number(id*ID_TO_POS);
    return posStr.toUtf8();
}

unsigned short ViewModel::posBytesToPos(QByteArray bytes)
{
    QString str(bytes);
    return str.toUShort();
}

void ViewModel::handleExport(size_t id)
{
    //如果它未被extern过,且没有其它password正在被extern
    auto it = std::find(externIdTable.begin(), externIdTable.end(), id);
    if(it == externIdTable.end() && !externingId)
    {
        //确保此时串口可用
        if(serialIsReady)
        {
            externingId = id;
            QByteArray password = model.bytesSelect(id, "password");

            unsigned short pos = id * ID_TO_POS;
            unsigned char cmd = (0X01 << 2);
            unsigned char len = password.length() + 1;
            QByteArray packet;
            packet.append((unsigned char)(pos >> 8)&0XFF);
            packet.append((unsigned char)(pos&0XFF));
            packet.append(cmd);
            packet.append(len);
            packet += password;

            emit packetIsReady(packet);
        }
        else
        {
            emit noAvailableSerial();
        }
    }

    //发出上一次extern的操作未完毕的提醒，不执行本次操作
    if(externingId != 0X00)
    {
        emit doingLastExternOperation();
    }
}

void ViewModel::getAck(QByteArray ack)
{
    if((unsigned char)*ack.begin() == NO_FINGER_VFY)
    {
        ++fingerVfyFailedTimes;
        emit noFingerVfy(fingerVfyFailedTimes);
        externingId = 0;
        accessingId = 0;
    }

    else if((unsigned char)*ack.begin() == DELETE_SUCCESS)
    {
        emit deleteSuccess();
    }

    else if((unsigned char)*ack.begin() == STORE_SUCCESS)
    {
        //如果存储成功对应的是extern成功
        if(model.bytesSelect(externingId, "externPos") == "0")
        {
            qDebug() << "export success: " << externingId;
            qDebug() << ack;

            emit externSuccess(externingId);
            localDelete();//将externingId置为0
        }
        else//对应update成功
        {
            qDebug() << "update success" << externingId;
            emit updateEnd(externingId);
            externingId = 0X00;
        }
    }
    else if((unsigned char)*ack.begin() == PASSWORD_DATA)
    {
        QByteArray passwordData = ack.mid(2);

        QString note = strDecryption(model.bytesSelect(accessingId, "note"));
        QString account = strDecryption(model.bytesSelect(accessingId, "account"));
        QString password = strDecryption(passwordData);
        accessingId = 0X00;
        emit accessEnd(note, account, password);
    }

    else
    {
        externingId = 0;
        accessingId = 0;
    }
}

void ViewModel::localDelete()
{
    if(!update("","password", externingId))
    {
        //empty
    }
    setIdExported(externingId);//存储外部地址，加入externIdTable
    externingId = 0X00;
}
