#ifndef CUSTOMERADDDIALOG_H
#define CUSTOMERADDDIALOG_H

#include <QDialog>
#include <sqlconnect.h>

namespace Ui {
class CustomerAddDialog;
}

class CustomerAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerAddDialog(QWidget *parent = nullptr);
    ~CustomerAddDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CustomerAddDialog *ui;
    SqlConnect * sql;

};

#endif // CUSTOMERADDDIALOG_H
