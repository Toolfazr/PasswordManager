#ifndef ACCESSITEM_H
#define ACCESSITEM_H

#include <QWidget>

namespace Ui {
class AccessItem;
}

class AccessItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccessItem(QWidget *parent = nullptr);
    ~AccessItem();

private:
    Ui::AccessItem *ui;
};

#endif // ACCESSITEM_H
