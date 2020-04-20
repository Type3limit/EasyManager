#ifndef PRODUCTINDIALOG_H
#define PRODUCTINDIALOG_H

#include <QDialog>
#include <sqlconnect.h>
#include <QImage>
#include <QComboBox>
namespace Ui {
class ProductInDialog;
}

class ProductInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductInDialog(QWidget *parent = nullptr);
    ~ProductInDialog();

private:
    Ui::ProductInDialog *ui;
    SqlConnect *sql;
};

#endif // PRODUCTINDIALOG_H
