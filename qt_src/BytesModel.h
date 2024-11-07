#ifndef BYTESMODEL_H
#define BYTESMODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <unordered_set>

class BytesModel
{
public:
    BytesModel();
    bool initDb();
    int bytesInsert(QByteArray bytes, QString attr);
    QByteArray bytesSelect(size_t id, QString attr);
    bool bytesDelete(size_t id);
    bool bytesUpdate(QByteArray bytes, QString attr, size_t id);
    std::unordered_map<size_t, QByteArray> getAllValidIdWithNote();
private:
    QSqlDatabase db;
};

#endif // BYTESMODEL_H
