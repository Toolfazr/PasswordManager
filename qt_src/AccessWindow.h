#ifndef ACCESSWINDOW_H
#define ACCESSWINDOW_H

#include <QWidget>

namespace Ui {
class AccessWindow;
}

class AccessWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AccessWindow(QWidget *parent = nullptr);
    ~AccessWindow();

private:
    Ui::AccessWindow *ui;
};

#endif // ACCESSWINDOW_H
