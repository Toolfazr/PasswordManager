#ifndef PASSWORDDISPLAYITEM_H
#define PASSWORDDISPLAYITEM_H

#include <QWidget>

namespace Ui {
class PasswordDisplayItem;
}

class PasswordDisplayItem : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
signals:
    void requestChange(PasswordDisplayItem* item);
public:
    explicit PasswordDisplayItem(QWidget *parent = nullptr);
    ~PasswordDisplayItem();
    inline void setAttr(QString str)
    {
        attr = str;
    }
private slots:
    void on_changeBtn_clicked();

private:
    Ui::PasswordDisplayItem *ui;
    QString attr;
};

#endif // PASSWORDDISPLAYITEM_H
