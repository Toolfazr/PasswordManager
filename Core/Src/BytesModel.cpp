#include "BytesModel.h"

BytesModel::BytesModel() {}

bool BytesModel::initDb()
{
    bool state = true;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../SQLite/test.db");

    if (!db.open())
    {
        qDebug() << "Failed to open database:" << db.lastError().text();
        state = false;
        return state;
    } else
    {
        qDebug() << "Database opened successfully!";
    }

    QSqlQuery query;
    //query.exec("DROP TABLE IF EXISTS test");

    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS test ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "note BLOB, "
        "account BLOB, "
        "password BLOB, "
        "externPos BLOB)"
        );

    if (!success) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        state = false;
        return state;
    } else {
        qDebug() << "Table created successfully!";
    }

    return state;
}

int BytesModel::bytesInsert(QByteArray bytes, QString attr)
{
    QSqlQuery query;

    QString queryString = QString("INSERT INTO test (%1) VALUES (:%1)").arg(attr);
    query.prepare(queryString);
    query.bindValue(QString(":%1").arg(attr), bytes);

    if (!query.exec()) {
        qDebug() << "Failed to insert BLOB data:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toInt();
}

QByteArray BytesModel::bytesSelect(size_t id, QString attr)
{
    QSqlQuery query;
    QString queryString = QString("SELECT (%1) FROM test WHERE id = :id").arg(attr);

    query.prepare(queryString);
    query.bindValue(":id", static_cast<qulonglong>(id));

    if (query.exec() && query.next()) {
        QByteArray blobData = query.value(0).toByteArray();
        return blobData;
    }
    else
    {
        qDebug() << "Failed to retrieve BLOB data:" << query.lastError().text();
        return QByteArray();
    }
}

bool BytesModel::bytesDelete(size_t id)
{
    QSqlQuery query;

    QString queryString = "DELETE FROM test WHERE id = :id";

    query.prepare(queryString);
    query.bindValue(":id", static_cast<qulonglong>(id));

    if (query.exec()) {
        qDebug() << "Record with id" << id << "deleted successfully.";
        return true;
    } else {
        qDebug() << "Failed to delete record:" << query.lastError().text();
        return false;
    }
}

bool BytesModel::bytesUpdate(QByteArray bytes, QString attr, size_t id)
{
    QSqlQuery query;

    QString queryString = QString("UPDATE test SET %1 = :value WHERE id = :id").arg(attr);

    query.prepare(queryString);

    query.bindValue(":value", bytes);
    query.bindValue(":id", static_cast<qulonglong>(id)); // id

    if (query.exec()) {
        qDebug() << "Record with id" << id << "updated successfully.";
        return true;
    } else {
        qDebug() << "Failed to update record:" << query.lastError().text();
        return false;
    }
}

std::unordered_map<size_t, QByteArray> BytesModel::getAllValidIdWithNote()
{
    QSqlQuery query;
    QString queryStr = "SELECT id, note FROM test";
    std::unordered_map<size_t, QByteArray> res;

    if (!query.exec(queryStr)) {
        qDebug() << "查询失败: " << query.lastError();
        return res;
    }

    while (query.next()) {
        size_t id = query.value(0).toInt();
        QByteArray noteBytes = query.value(1).toByteArray();
        res.insert({id, noteBytes});
    }

    return res;
}
