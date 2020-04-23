#ifndef CUSTOMERVIEWDIALOG_H
#define CUSTOMERVIEWDIALOG_H

#include <QDialog>
#include <sqlconnect.h>
#include <QComboBox>

namespace Ui {
class CustomerViewDialog;
}

class CustomerViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerViewDialog(QWidget *parent = nullptr);
    ~CustomerViewDialog();

private:
    void Initilaize();

private slots:

    void on_CustomerBox_activated(int index);

private:
    Ui::CustomerViewDialog *ui;
    SqlConnect *sql;
    QString * Names;
    QString * IDs;
    QString * Contancts;
    QString * Amounts;
    QString * RegistTimes;
};

#endif // CUSTOMERVIEWDIALOG_H
