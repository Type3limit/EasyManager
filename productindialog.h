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
    void Initlize();


public:
    explicit ProductInDialog(QWidget *parent = nullptr);
    ~ProductInDialog();

private slots:

    void on_ProductChooseBox_activated(int index);

    void on_ConfirmButton_clicked();

private:
    Ui::ProductInDialog *ui;
    SqlConnect *sql;
    QString *IDs;
    QString *Names;
    QString *Images;

};

#endif // PRODUCTINDIALOG_H
