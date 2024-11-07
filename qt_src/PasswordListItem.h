#ifndef PASSWORDLISTITEM_H
#define PASSWORDLISTITEM_H

#include <QWidget>
#include <QStandardItem>

namespace Ui {
class PasswordListItem;
}

class PasswordListItem : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
public:
    explicit PasswordListItem(QWidget *parent = nullptr);
    ~PasswordListItem();
    inline void setId(size_t id)
    {
        this->id = id;
    }
    inline size_t getId(void)
    {
        return this->id;
    }
signals:
    void requestDelete(PasswordListItem* item, size_t id);
    void requestAccess(PasswordListItem* item);
    void requestExport(size_t id);
private slots:

    void on_Delete_clicked();
    void on_Access_clicked();
    void on_More_clicked();

private:
    Ui::PasswordListItem *ui;
    size_t id;
};

#endif // PASSWORDLISTITEM_H
