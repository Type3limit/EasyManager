#ifndef CUSTOMERRECHARGEDIALOG_H
#define CUSTOMERRECHARGEDIALOG_H

#include <QDialog>
#include <sqlconnect.h>

namespace Ui {
class CustomerRechargeDialog;
}

class CustomerRechargeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerRechargeDialog(QWidget *parent = nullptr);
    ~CustomerRechargeDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CustomerRechargeDialog *ui;
    SqlConnect* sql;
};

#endif // CUSTOMERRECHARGEDIALOG_H
