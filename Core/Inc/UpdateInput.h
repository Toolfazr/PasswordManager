#ifndef UPDATEINPUT_H
#define UPDATEINPUT_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class UpdateInput;
}

class UpdateInput : public QDialog
{
    Q_OBJECT
signals:
    void inputEnd(QString str);
    void noInput();
public:
    explicit UpdateInput(QWidget *parent = nullptr);
    ~UpdateInput();
public slots:
    void UpdateFormShow();
private slots:
    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    void closeEvent(QCloseEvent* event);
    Ui::UpdateInput *ui;
};

#endif // UPDATEINPUT_H
