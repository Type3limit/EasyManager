#ifndef PRODUCTINMODELDIALOG_H
#define PRODUCTINMODELDIALOG_H

#include <QDialog>
#include <productadddialog.h>
#include <productindialog.h>

namespace Ui {
class ProductInModelDialog;
}

class ProductInModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductInModelDialog(QWidget *parent = nullptr);
    ~ProductInModelDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ProductInModelDialog *ui;
    ProductInDialog productInDialog;
    ProductAddDialog productAddDialog;
};

#endif // PRODUCTINMODELDIALOG_H
