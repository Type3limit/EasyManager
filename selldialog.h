#ifndef SELLDIALOG_H
#define SELLDIALOG_H

#include <QDialog>
#include <sqlconnect.h>

namespace Ui {
class SellDialog;
}

class SellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SellDialog(QWidget *parent = nullptr);
    ~SellDialog();

public:
    void Initialize();
    bool useable;

private slots:
    void on_ConfrimButton_clicked();

    void on_ProductChooseBox_activated(int index);

    void on_UserChoosenBox_activated(int index);

    void on_NumberSpinBox_valueChanged(int arg1);

private:
    Ui::SellDialog *ui;
    SqlConnect* sql;



    int CustomerCount;
    int ProductCount;

    int current_product_index;

    QString* CustomerName;
    QString* CustomerAcount;
    QString* CustomerPasswd;

    QString* ProductID;
    QString* ProductName;
    QString* ProductImage;
    QString* ProductPrice;
};

#endif // SELLDIALOG_H
