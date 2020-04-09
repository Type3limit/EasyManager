#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H

#include <QDialog>
#include <sqlconnect.h>
namespace Ui {
class RegistDialog;
}

class RegistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistDialog(QWidget *parent = nullptr);
    ~RegistDialog();

private slots:
    void on_RegistButton_clicked();

private:
    Ui::RegistDialog *ui;
    SqlConnect * sql;
};

#endif // REGISTDIALOG_H
