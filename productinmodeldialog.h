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

private:
    Ui::ProductInModelDialog *ui;
    ProductInDialog productInDialog;
    ProductAddDialog productAddDialog;
};

#endif // PRODUCTINMODELDIALOG_H
